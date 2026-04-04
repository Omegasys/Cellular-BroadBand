#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/src/modem/ID/ID.conf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/imsi_log.txt"      // Path to log file where IMSI rotation is logged

// Function to read the IMSI and rotation interval from the .conf file
int read_config(char *imsi, int *rotate_interval) {
    FILE *config_file = fopen(/src/modem/ID/ID.conf, "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), config_file)) {
        if (strncmp(line, "imsi=", 5) == 0) {
            strcpy(imsi, line + 5);  // Get the IMSI number
            imsi[strcspn(imsi, "\n")] = '\0';  // Remove trailing newline
        } else if (strncmp(line, "rotate_interval=", 16) == 0) {
            *rotate_interval = atoi(line + 16);  // Get the rotate interval (in seconds)
        }
    }

    fclose(config_file);
    return 0;
}

// Function to rotate the IMSI based on the designated time interval
void rotate_imsi(const char *imsi, const int rotate_interval) {
    FILE *log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    time_t current_time;
    struct tm *time_info;
    char time_buffer[80];

    // Get current time
    time(&current_time);
    time_info = localtime(&current_time);

    // Format the time string
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_info);

    // Log the current IMSI and timestamp
    fprintf(log_file, "Timestamp: %s, IMSI: %s\n", time_buffer, imsi);

    fclose(log_file);
}

// Function to handle the IMSI rotation
void start_imsi_rotation() {
    char imsi[128];
    int rotate_interval = 0;

    // Read configuration file to get IMSI and interval
    if (read_config(imsi, &rotate_interval) != 0) {
        fprintf(stderr, "Failed to read configuration.\n");
        return;
    }

    // Check if the interval is valid
    if (rotate_interval <= 0) {
        fprintf(stderr, "Invalid rotation interval.\n");
        return;
    }

    printf("Starting IMSI rotation every %d seconds...\n", rotate_interval);

    while (1) {
        // Rotate the IMSI and log it
        rotate_imsi(imsi, rotate_interval);

        // Sleep for the specified interval
        sleep(rotate_interval);
    }
}

int main() {
    // Start rotating the IMSI
    start_imsi_rotation();

    return 0;
}

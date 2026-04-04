#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/src/modem/ID/ID.conf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/inzi_log.txt"     // Path to log file where INZI rotation is logged

// Function to read the INZI and rotation interval from the .conf file
int read_config(char *inzi, int *rotate_interval) {
    FILE *config_file = fopen(/src/modem/ID/ID.conf, "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), config_file)) {
        if (strncmp(line, "inzi=", 5) == 0) {
            strcpy(inzi, line + 5);  // Get the INZI number
            inzi[strcspn(inzi, "\n")] = '\0';  // Remove trailing newline
        } else if (strncmp(line, "rotate_interval=", 16) == 0) {
            *rotate_interval = atoi(line + 16);  // Get the rotate interval (in seconds)
        }
    }

    fclose(config_file);
    return 0;
}

// Function to rotate the INZI based on the designated time interval
void rotate_inzi(const char *inzi, const int rotate_interval) {
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

    // Log the current INZI and timestamp
    fprintf(log_file, "Timestamp: %s, INZI: %s\n", time_buffer, inzi);

    fclose(log_file);
}

// Function to handle the INZI rotation
void start_inzi_rotation() {
    char inzi[128];
    int rotate_interval = 0;

    // Read configuration file to get INZI and interval
    if (read_config(inzi, &rotate_interval) != 0) {
        fprintf(stderr, "Failed to read configuration.\n");
        return;
    }

    // Check if the interval is valid
    if (rotate_interval <= 0) {
        fprintf(stderr, "Invalid rotation interval.\n");
        return;
    }

    printf("Starting INZI rotation every %d seconds...\n", rotate_interval);

    while (1) {
        // Rotate the INZI and log it
        rotate_inzi(inzi, rotate_interval);

        // Sleep for the specified interval
        sleep(rotate_interval);
    }
}

int main() {
    // Start rotating the INZI
    start_inzi_rotation();

    return 0;
}

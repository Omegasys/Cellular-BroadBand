#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/etc/device_config.comf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/ad_id_log.txt"       // Path to log file where AD-ID rotation is logged

// Function to read the AD-ID and rotation interval from the .comf file
int read_config(char *ad_id, int *rotate_interval) {
    FILE *config_file = fopen(CONFIG_FILE_PATH, "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), config_file)) {
        if (strncmp(line, "ad_id=", 6) == 0) {
            strcpy(ad_id, line + 6);  // Get the AD-ID
            ad_id[strcspn(ad_id, "\n")] = '\0';  // Remove trailing newline
        } else if (strncmp(line, "rotate_interval=", 16) == 0) {
            *rotate_interval = atoi(line + 16);  // Get the rotate interval (in seconds)
        }
    }

    fclose(config_file);
    return 0;
}

// Function to rotate the AD-ID based on the designated time interval
void rotate_ad_id(const char *ad_id, const int rotate_interval) {
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

    // Log the current AD-ID and timestamp
    fprintf(log_file, "Timestamp: %s, AD-ID: %s\n", time_buffer, ad_id);

    fclose(log_file);
}

// Function to handle the AD-ID rotation
void start_ad_id_rotation() {
    char ad_id[128];
    int rotate_interval = 0;

    // Read configuration file to get AD-ID and interval
    if (read_config(ad_id, &rotate_interval) != 0) {
        fprintf(stderr, "Failed to read configuration.\n");
        return;
    }

    // Check if the interval is valid
    if (rotate_interval <= 0) {
        fprintf(stderr, "Invalid rotation interval.\n");
        return;
    }

    printf("Starting AD-ID rotation every %d seconds...\n", rotate_interval);

    while (1) {
        // Rotate the AD-ID and log it
        rotate_ad_id(ad_id, rotate_interval);

        // Sleep for the specified interval
        sleep(rotate_interval);
    }
}

int main() {
    // Start rotating the AD-ID
    start_ad_id_rotation();

    return 0;
}

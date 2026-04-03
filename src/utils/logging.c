#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define LOG_FILE "application.log"  // Log file name

// Log levels
typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
} LogLevel;

// Mutex for thread-safety (for multi-threaded environments)
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to get the current timestamp as a string
const char *get_current_timestamp() {
    static char timestamp[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    return timestamp;
}

// Function to log a message to both the console and a log file
void log_message(LogLevel level, const char *format, ...) {
    // Lock mutex for thread safety
    pthread_mutex_lock(&log_mutex);

    // Open the log file in append mode
    FILE *log_file = fopen(LOG_FILE, "a");
    if (!log_file) {
        fprintf(stderr, "Failed to open log file %s\n", LOG_FILE);
        pthread_mutex_unlock(&log_mutex);
        return;
    }

    // Get the current timestamp
    const char *timestamp = get_current_timestamp();

    // Determine the log level as a string
    const char *level_str = NULL;
    switch (level) {
        case LOG_LEVEL_INFO:    level_str = "INFO"; break;
        case LOG_LEVEL_WARNING: level_str = "WARNING"; break;
        case LOG_LEVEL_ERROR:   level_str = "ERROR"; break;
        default:                level_str = "UNKNOWN"; break;
    }

    // Format the log message
    va_list args;
    va_start(args, format);
    char formatted_message[1024];
    vsnprintf(formatted_message, sizeof(formatted_message), format, args);
    va_end(args);

    // Log to console (stdout)
    printf("[%s] [%s] %s\n", timestamp, level_str, formatted_message);

    // Log to file
    fprintf(log_file, "[%s] [%s] %s\n", timestamp, level_str, formatted_message);

    // Close the log file
    fclose(log_file);

    // Unlock mutex
    pthread_mutex_unlock(&log_mutex);
}

// Logging convenience functions for different log levels

void log_info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_INFO, format, args);
    va_end(args);
}

void log_warning(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_WARNING, format, args);
    va_end(args);
}

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

// Function to rotate logs (optional, for when the log file becomes too large)
void rotate_log_file() {
    // Check if the log file exists and its size
    FILE *log_file = fopen(LOG_FILE, "r");
    if (log_file) {
        fseek(log_file, 0, SEEK_END);
        long file_size = ftell(log_file);
        fclose(log_file);

        // If the file is too large (e.g., > 5MB), rotate the logs
        if (file_size > 5 * 1024 * 1024) {
            // Rename the old log file to create a backup (e.g., "application.log.1")
            rename(LOG_FILE, "application.log.1");

            // Create a new log file
            log_file = fopen(LOG_FILE, "w");
            if (log_file) {
                fclose(log_file);  // Just create an empty log file
            }
        }
    }
}

int main() {
    // Example usage of logging functions
    log_info("This is an info message.");
    log_warning("This is a warning message.");
    log_error("This is an error message.");

    // Optional: Rotate the log file if it's too large
    rotate_log_file();

    return 0;
}

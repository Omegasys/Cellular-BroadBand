#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdarg.h>

// Log levels
typedef enum {
    LOG_LEVEL_INFO,    // Informational messages
    LOG_LEVEL_WARNING, // Warning messages
    LOG_LEVEL_ERROR    // Error messages
} LogLevel;

// Function Prototypes

/**
 * @brief Logs a message with the specified log level.
 * 
 * @param level The log level (INFO, WARNING, ERROR).
 * @param format The format string for the log message.
 * @param ... The values to format into the message.
 */
void log_message(LogLevel level, const char *format, ...);

/**
 * @brief Logs an informational message.
 * 
 * @param format The format string for the log message.
 * @param ... The values to format into the message.
 */
void log_info(const char *format, ...);

/**
 * @brief Logs a warning message.
 * 
 * @param format The format string for the log message.
 * @param ... The values to format into the message.
 */
void log_warning(const char *format, ...);

/**
 * @brief Logs an error message.
 * 
 * @param format The format string for the log message.
 * @param ... The values to format into the message.
 */
void log_error(const char *format, ...);

/**
 * @brief Rotates the log file if it exceeds a certain size.
 * 
 * This function checks if the log file exceeds a defined size (e.g., 5MB) and rotates it by renaming the current log file.
 */
void rotate_log_file(void);

#endif // LOGGING_H

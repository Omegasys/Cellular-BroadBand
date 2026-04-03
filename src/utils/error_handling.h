#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>

// Define error codes for various types of failures
typedef enum {
    ERROR_NONE = 0,             // No error
    ERROR_MEMORY_ALLOCATION,    // Memory allocation failed
    ERROR_FILE_NOT_FOUND,       // File could not be found or opened
    ERROR_INVALID_ARGUMENT,     // Invalid function arguments
    ERROR_NETWORK_FAILURE,      // Network failure
    ERROR_UNKNOWN               // Unknown error
} ErrorCode;

// Function prototypes

/**
 * @brief Retrieves the error message corresponding to a given error code.
 * 
 * @param code The error code to get the error string for.
 * @return A string describing the error code.
 */
const char* get_error_string(ErrorCode code);

/**
 * @brief Handles an error by logging it and optionally terminating the program.
 * 
 * @param code The error code.
 * @param context A description of the context where the error occurred.
 * @param fatal If true, the program will terminate after handling the error.
 */
void handle_error(ErrorCode code, const char *context, int fatal);

/**
 * @brief Handles a memory allocation failure by allocating memory and handling any errors.
 * 
 * @param size The size of memory to allocate.
 * @return A pointer to the allocated memory.
 */
void* handle_memory_error(size_t size);

/**
 * @brief Handles a file opening error by opening the specified file.
 * 
 * @param filename The name of the file to open.
 * @return A file pointer to the opened file.
 */
FILE* handle_file_error(const char *filename);

/**
 * @brief Handles an invalid argument error.
 * 
 * @param arg The invalid argument that caused the error.
 */
void handle_invalid_argument_error(const char *arg);

/**
 * @brief Handles a network failure error.
 * 
 * @param context A description of the network failure context.
 */
void handle_network_failure(const char *context);

/**
 * @brief Simulates the rotation of the log file if it exceeds a certain size.
 */
void rotate_log_file(void);

#endif // ERROR_HANDLING_H

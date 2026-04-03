#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "logging.h"

// Define error codes
typedef enum {
    ERROR_NONE = 0,
    ERROR_MEMORY_ALLOCATION,
    ERROR_FILE_NOT_FOUND,
    ERROR_INVALID_ARGUMENT,
    ERROR_NETWORK_FAILURE,
    ERROR_UNKNOWN
} ErrorCode;

// Function to get a string representation of an error code
const char* get_error_string(ErrorCode code) {
    switch (code) {
        case ERROR_MEMORY_ALLOCATION:
            return "Memory allocation failed";
        case ERROR_FILE_NOT_FOUND:
            return "File not found";
        case ERROR_INVALID_ARGUMENT:
            return "Invalid argument provided";
        case ERROR_NETWORK_FAILURE:
            return "Network failure occurred";
        case ERROR_UNKNOWN:
        default:
            return "Unknown error";
    }
}

// Function to handle an error by logging it and possibly exiting
void handle_error(ErrorCode code, const char *context, int fatal) {
    // Log the error message with context
    log_error("Error: %s. Context: %s. Error Code: %d", get_error_string(code), context, code);

    // If the error is fatal, exit the program with the error code
    if (fatal) {
        log_error("Fatal error encountered. Exiting...");
        exit(code);  // Exit with the error code
    }
}

// Function to handle memory allocation failures
void* handle_memory_error(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        handle_error(ERROR_MEMORY_ALLOCATION, "Memory allocation failed", 1); // Fatal error
    }
    return ptr;
}

// Function to handle file opening errors
FILE* handle_file_error(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        handle_error(ERROR_FILE_NOT_FOUND, filename, 1);  // Fatal error
    }
    return file;
}

// Function to handle invalid argument errors
void handle_invalid_argument_error(const char *arg) {
    handle_error(ERROR_INVALID_ARGUMENT, arg, 0); // Non-fatal error
}

// Function to simulate a network failure error
void handle_network_failure(const char *context) {
    handle_error(ERROR_NETWORK_FAILURE, context, 0); // Non-fatal error
}

// Example function to simulate an error during file operations
void simulate_file_operation() {
    FILE *file = handle_file_error("non_existent_file.txt");
    // Further operations would be performed here if the file is opened successfully
    fclose(file);
}

int main() {
    // Simulate a memory allocation error
    char *data = (char *)handle_memory_error(1024);

    // Simulate a file operation that results in an error
    simulate_file_operation();

    // Simulate invalid argument error
    handle_invalid_argument_error("Null pointer argument");

    // Simulate a network failure
    handle_network_failure("Unable to connect to the server");

    free(data);
    return 0;
}

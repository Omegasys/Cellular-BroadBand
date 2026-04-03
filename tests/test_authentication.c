#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "authentication.h"
#include "logging.h"

// Function to test valid authentication
void test_valid_authentication() {
    const char *valid_username = "user123";
    const char *valid_password = "password456";

    log_info("Testing valid authentication...");
    
    if (authenticate_user(valid_username, valid_password)) {
        log_info("Test passed: Valid credentials successfully authenticated.");
    } else {
        log_error("Test failed: Valid credentials failed authentication.");
    }
}

// Function to test invalid authentication (wrong username)
void test_invalid_username() {
    const char *invalid_username = "invalid_user";
    const char *valid_password = "password456";

    log_info("Testing invalid username authentication...");

    if (!authenticate_user(invalid_username, valid_password)) {
        log_info("Test passed: Invalid username correctly rejected.");
    } else {
        log_error("Test failed: Invalid username was accepted.");
    }
}

// Function to test invalid authentication (wrong password)
void test_invalid_password() {
    const char *valid_username = "user123";
    const char *invalid_password = "wrongpassword";

    log_info("Testing invalid password authentication...");

    if (!authenticate_user(valid_username, invalid_password)) {
        log_info("Test passed: Invalid password correctly rejected.");
    } else {
        log_error("Test failed: Invalid password was accepted.");
    }
}

// Function to test authentication with both username and password incorrect
void test_invalid_credentials() {
    const char *invalid_username = "invalid_user";
    const char *invalid_password = "wrongpassword";

    log_info("Testing invalid credentials authentication...");

    if (!authenticate_user(invalid_username, invalid_password)) {
        log_info("Test passed: Invalid credentials correctly rejected.");
    } else {
        log_error("Test failed: Invalid credentials were accepted.");
    }
}

int main() {
    // Initialize the logging system for the test
    log_info("Running authentication tests...");

    // Run the test cases
    test_valid_authentication();
    test_invalid_username();
    test_invalid_password();
    test_invalid_credentials();

    log_info("Authentication tests completed.");

    return 0;
}

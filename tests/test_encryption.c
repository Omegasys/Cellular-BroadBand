#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encryption.h"
#include "logging.h"

// A simple test for the encryption and decryption functions
void test_encryption() {
    // Original data (dummy data for testing)
    uint8_t original_data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t data_length = sizeof(original_data);

    // Encrypt the data
    uint8_t *encrypted_data = encrypt_data(original_data, data_length);
    if (!encrypted_data) {
        log_error("Encryption failed. Exiting.");
        return;
    }

    log_info("Original data: ");
    for (size_t i = 0; i < data_length; i++) {
        printf("%02X ", original_data[i]);
    }
    printf("\n");

    log_info("Encrypted data: ");
    for (size_t i = 0; i < data_length; i++) {
        printf("%02X ", encrypted_data[i]);
    }
    printf("\n");

    // Decrypt the data
    uint8_t *decrypted_data = decrypt_data(encrypted_data, data_length);
    if (!decrypted_data) {
        log_error("Decryption failed. Exiting.");
        free(encrypted_data);
        return;
    }

    log_info("Decrypted data: ");
    for (size_t i = 0; i < data_length; i++) {
        printf("%02X ", decrypted_data[i]);
    }
    printf("\n");

    // Verify if the decrypted data matches the original data
    if (memcmp(original_data, decrypted_data, data_length) == 0) {
        log_info("Encryption and decryption succeeded. Data matches.");
    } else {
        log_error("Encryption and decryption failed. Data does not match.");
    }

    // Clean up allocated memory
    free(encrypted_data);
    free(decrypted_data);
}

int main() {
    // Initialize the logging system for the test
    log_info("Running encryption tests...");

    // Run the encryption test
    test_encryption();

    log_info("Encryption tests completed.");

    return 0;
}

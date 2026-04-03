#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lte_modem.h"
#include "logging.h"
#include "packet_handler.h"
#include "encryption.h"
#include "authentication.h"
#include "error_handling.h"

// Function to test the full flow: Packet creation, encryption, authentication, and sending
void test_lte_modem_flow() {
    const char *username = "user123";
    const char *password = "password456";

    // Step 1: Authenticate the user
    log_info("Starting LTE modem flow test...");
    
    if (!authenticate_user(username, password)) {
        log_error("Authentication failed. Exiting LTE modem flow test.");
        handle_error(ERROR_UNKNOWN, "User authentication", 1);  // Fatal error
    }

    log_info("User authenticated successfully.");

    // Step 2: Create a packet
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t payload_length = sizeof(payload);
    
    Packet *packet = create_packet(payload, payload_length);
    if (!packet) {
        log_error("Packet creation failed. Exiting LTE modem flow test.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Packet creation", 1);  // Fatal error
    }

    log_info("Packet created successfully. Payload size: %d", packet->length);

    // Step 3: Encrypt the packet
    uint8_t *encrypted_data = encrypt_data(packet->payload, packet->length);
    if (!encrypted_data) {
        log_error("Encryption failed. Exiting LTE modem flow test.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Encryption", 1);  // Fatal error
    }

    log_info("Packet encrypted successfully.");

    // Step 4: Simulate sending the encrypted packet
    log_info("Sending encrypted packet...");
    // In a real LTE modem, this would involve network communication
    // For this test, we just simulate the action

    // Step 5: Simulate receiving the encrypted packet and decrypting it
    log_info("Simulating reception of encrypted packet...");
    uint8_t *decrypted_data = decrypt_data(encrypted_data, packet->length);
    if (!decrypted_data) {
        log_error("Decryption failed. Exiting LTE modem flow test.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Decryption", 1);  // Fatal error
    }

    log_info("Packet decrypted successfully.");

    // Step 6: Validate that the decrypted data matches the original data
    if (memcmp(packet->payload, decrypted_data, packet->length) == 0) {
        log_info("Test passed: Decrypted data matches original data.");
    } else {
        log_error("Test failed: Decrypted data does not match original data.");
    }

    // Clean up allocated memory
    free(encrypted_data);
    free(decrypted_data);
    free_packet(packet);

    log_info("LTE modem flow test completed.");
}

// Function to test error handling in LTE modem flow
void test_lte_modem_error_handling() {
    log_info("Testing LTE modem error handling...");

    // Simulate an authentication failure
    const char *invalid_username = "invalid_user";
    const char *invalid_password = "wrongpassword";

    if (authenticate_user(invalid_username, invalid_password)) {
        log_error("Authentication unexpectedly succeeded.");
    } else {
        log_info("Test passed: Invalid credentials correctly rejected.");
    }

    // Simulate packet creation failure (e.g., out of memory)
    uint8_t *large_payload = (uint8_t *)malloc(1024 * 1024 * 1024);  // Allocate 1GB of memory to simulate failure
    if (!large_payload) {
        log_info("Test passed: Memory allocation failed as expected.");
    } else {
        log_error("Test failed: Memory allocation unexpectedly succeeded.");
        free(large_payload);
    }

    log_info("LTE modem error handling test completed.");
}

// Function to test LTE modem behavior under network conditions (simulation)
void test_lte_modem_network_conditions() {
    log_info("Testing LTE modem under network conditions...");

    // Simulate packet creation and send it under "bad network" conditions
    uint8_t payload[] = {0x01, 0x02, 0x03};
    size_t payload_length = sizeof(payload);

    Packet *packet = create_packet(payload, payload_length);
    if (!packet) {
        log_error("Packet creation failed. Exiting network condition test.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Packet creation", 1);  // Fatal error
    }

    log_info("Packet created successfully. Payload size: %d", packet->length);

    // Simulate a network failure scenario (e.g., packet not sent)
    int network_status = 0;  // 0 indicates network failure, 1 success
    if (network_status == 0) {
        log_error("Network failure: Packet transmission failed.");
    } else {
        log_info("Network condition simulated: Packet sent successfully.");
    }

    // Clean up
    free_packet(packet);

    log_info("LTE modem network condition test completed.");
}

int main() {
    // Initialize the logging system for the test
    log_info("Running LTE modem tests...");

    // Run full LTE modem flow test
    test_lte_modem_flow();

    // Test LTE modem error handling
    test_lte_modem_error_handling();

    // Test LTE modem under network conditions
    test_lte_modem_network_conditions();

    log_info("LTE modem tests completed.");

    return 0;
}

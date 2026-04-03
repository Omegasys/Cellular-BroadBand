#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "packet_handler.h"
#include "logging.h"

// Function to test packet creation
void test_packet_creation() {
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t payload_length = sizeof(payload);

    log_info("Testing packet creation...");

    // Create a packet with the given payload
    Packet *packet = create_packet(payload, payload_length);
    if (!packet) {
        log_error("Packet creation failed. Exiting.");
        return;
    }

    log_info("Packet created successfully. Payload size: %d", packet->length);

    // Verify the packet's payload
    if (memcmp(packet->payload, payload, payload_length) == 0) {
        log_info("Test passed: Packet payload matches expected data.");
    } else {
        log_error("Test failed: Packet payload does not match expected data.");
    }

    // Clean up the allocated memory
    free_packet(packet);
}

// Function to test adding data to an existing packet
void test_packet_add_data() {
    uint8_t initial_payload[] = {0x01, 0x02, 0x03};
    size_t initial_payload_length = sizeof(initial_payload);
    
    uint8_t additional_data[] = {0x04, 0x05};
    size_t additional_data_length = sizeof(additional_data);

    log_info("Testing adding data to an existing packet...");

    // Create a packet with the initial payload
    Packet *packet = create_packet(initial_payload, initial_payload_length);
    if (!packet) {
        log_error("Packet creation failed. Exiting.");
        return;
    }

    // Add additional data to the packet
    if (add_data_to_packet(packet, additional_data, additional_data_length) != 0) {
        log_error("Failed to add data to packet.");
        free_packet(packet);
        return;
    }

    // Verify the packet's new payload
    uint8_t expected_payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    if (memcmp(packet->payload, expected_payload, sizeof(expected_payload)) == 0) {
        log_info("Test passed: Data successfully added to packet.");
    } else {
        log_error("Test failed: Packet payload does not match expected data after adding data.");
    }

    // Clean up the allocated memory
    free_packet(packet);
}

// Function to test packet checksum calculation
void test_packet_checksum() {
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t payload_length = sizeof(payload);

    log_info("Testing packet checksum calculation...");

    // Create a packet with the given payload
    Packet *packet = create_packet(payload, payload_length);
    if (!packet) {
        log_error("Packet creation failed. Exiting.");
        return;
    }

    // Calculate checksum for the packet
    uint16_t checksum = calculate_packet_checksum(packet);
    log_info("Calculated checksum: %04X", checksum);

    // Verify that the checksum calculation is correct
    uint16_t expected_checksum = 0x0F1E; // Example checksum (replace with actual expected checksum)
    if (checksum == expected_checksum) {
        log_info("Test passed: Checksum matches expected value.");
    } else {
        log_error("Test failed: Checksum does not match expected value.");
    }

    // Clean up the allocated memory
    free_packet(packet);
}

// Function to test packet validation (e.g., check if a packet is valid)
void test_packet_validation() {
    uint8_t valid_payload[] = {0x01, 0x02, 0x03, 0x04};
    size_t valid_payload_length = sizeof(valid_payload);

    uint8_t invalid_payload[] = {0x01, 0x02}; // Invalid payload (too short)
    size_t invalid_payload_length = sizeof(invalid_payload);

    log_info("Testing packet validation...");

    // Create a valid packet
    Packet *valid_packet = create_packet(valid_payload, valid_payload_length);
    if (!valid_packet) {
        log_error("Valid packet creation failed. Exiting.");
        return;
    }

    // Validate the valid packet
    if (validate_packet(valid_packet)) {
        log_info("Test passed: Valid packet passed validation.");
    } else {
        log_error("Test failed: Valid packet failed validation.");
    }

    // Create an invalid packet
    Packet *invalid_packet = create_packet(invalid_payload, invalid_payload_length);
    if (!invalid_packet) {
        log_error("Invalid packet creation failed. Exiting.");
        return;
    }

    // Validate the invalid packet
    if (!validate_packet(invalid_packet)) {
        log_info("Test passed: Invalid packet failed validation.");
    } else {
        log_error("Test failed: Invalid packet passed validation.");
    }

    // Clean up the allocated memory
    free_packet(valid_packet);
    free_packet(invalid_packet);
}

int main() {
    // Initialize the logging system for the test
    log_info("Running packet handler tests...");

    // Run the test cases
    test_packet_creation();
    test_packet_add_data();
    test_packet_checksum();
    test_packet_validation();

    log_info("Packet handler tests completed.");

    return 0;
}

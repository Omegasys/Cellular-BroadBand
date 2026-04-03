#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "error_handling.h"
#include "packet_handler.h"
#include "encryption.h"
#include "authentication.h"

int main() {
    // Initialize the logging system
    log_info("Starting LTE Modem Application");

    // Example of packet creation and handling
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Packet *packet = create_packet(payload, sizeof(payload));
    if (!packet) {
        log_error("Failed to create packet. Exiting.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Creating packet", 1);  // Fatal error
    }

    log_info("Packet created successfully. Payload size: %d", packet->length);

    // Simulate encryption of the packet payload
    uint8_t *encrypted_data = encrypt_data(packet->payload, packet->length);
    if (!encrypted_data) {
        log_error("Failed to encrypt data. Exiting.");
        handle_error(ERROR_MEMORY_ALLOCATION, "Encrypting data", 1);  // Fatal error
    }

    log_info("Data encrypted successfully.");

    // Simulate authentication process
    if (!authenticate_user("user123", "password456")) {
        log_error("Authentication failed. Exiting.");
        handle_error(ERROR_UNKNOWN, "Authentication", 1);  // Fatal error
    }

    log_info("User authenticated successfully.");

    // Simulate sending the packet (in this case, just print to log)
    log_info("Sending packet with encrypted data...");
    // Here you'd send the packet over the network

    // Log completion
    log_info("LTE Modem Application completed successfully.");

    // Free allocated memory
    free(encrypted_data);
    free_packet(packet);

    return 0;
}

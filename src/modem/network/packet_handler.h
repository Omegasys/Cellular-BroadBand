#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <stdint.h>
#include <stddef.h>

// Constants for packet construction
#define MAX_PACKET_SIZE 1024  // Maximum size of a packet
#define HEADER_SIZE 4         // 4 bytes for the header (e.g., packet length or type)
#define CHECKSUM_SIZE 1       // 1 byte for checksum (simple XOR checksum)

// Packet structure
typedef struct {
    uint32_t length;     // Total length of the packet (header + payload)
    uint8_t *payload;    // Pointer to the packet payload
    uint8_t checksum;    // Simple checksum for integrity validation
} Packet;

// Function Prototypes

/**
 * @brief Calculates a simple XOR checksum for a given buffer.
 * 
 * @param data The data buffer to calculate the checksum for.
 * @param length The length of the data buffer.
 * @return The XOR checksum.
 */
uint8_t calculate_checksum(const uint8_t *data, size_t length);

/**
 * @brief Creates a packet with the given payload.
 * 
 * @param payload The data to include in the packet.
 * @param payload_length The length of the payload.
 * @return A pointer to the created packet, or NULL on error.
 */
Packet *create_packet(const uint8_t *payload, size_t payload_length);

/**
 * @brief Parses a raw data buffer into a packet and verifies its integrity.
 * 
 * @param data The raw data buffer to parse.
 * @param data_length The length of the raw data buffer.
 * @param packet The parsed packet that will be filled with data.
 * @return 0 on success, or -1 on error (e.g., checksum failure).
 */
int parse_packet(const uint8_t *data, size_t data_length, Packet *packet);

/**
 * @brief Prints a packet's details for debugging.
 * 
 * @param packet The packet to print.
 */
void print_packet(Packet *packet);

/**
 * @brief Frees the memory allocated for a packet.
 * 
 * @param packet The packet to free.
 */
void free_packet(Packet *packet);

#endif // PACKET_HANDLER_H

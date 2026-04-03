#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_PACKET_SIZE 1024  // Maximum size of a packet
#define HEADER_SIZE 4        // 4 bytes for the header (e.g., packet length or type)
#define CHECKSUM_SIZE 1      // 1 byte for checksum (simple XOR checksum)

// Packet structure
typedef struct {
    uint32_t length;     // Total length of the packet (header + payload)
    uint8_t *payload;    // Pointer to the packet payload
    uint8_t checksum;    // Simple checksum for integrity validation
} Packet;

// Function to calculate a simple XOR checksum for a given buffer
uint8_t calculate_checksum(const uint8_t *data, size_t length) {
    uint8_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum ^= data[i];  // XOR each byte of the data
    }
    return checksum;
}

// Function to construct a packet (header + payload)
Packet *create_packet(const uint8_t *payload, size_t payload_length) {
    // Allocate memory for the packet
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    if (!packet) {
        fprintf(stderr, "Memory allocation failed for packet\n");
        return NULL;
    }

    packet->length = HEADER_SIZE + payload_length + CHECKSUM_SIZE;  // Length = header + payload + checksum
    packet->payload = (uint8_t *)malloc(payload_length);
    if (!packet->payload) {
        free(packet);
        fprintf(stderr, "Memory allocation failed for packet payload\n");
        return NULL;
    }

    memcpy(packet->payload, payload, payload_length);  // Copy the payload into the packet

    // Calculate checksum and append it to the packet
    packet->checksum = calculate_checksum(packet->payload, payload_length);

    return packet;
}

// Function to parse a packet and validate its integrity
int parse_packet(const uint8_t *data, size_t data_length, Packet *packet) {
    if (data_length < HEADER_SIZE + CHECKSUM_SIZE) {
        fprintf(stderr, "Packet is too small to be valid\n");
        return -1;
    }

    // Extract the packet length and allocate memory for the payload
    packet->length = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];  // Assuming a 4-byte length in big-endian
    if (data_length != packet->length) {
        fprintf(stderr, "Packet length mismatch\n");
        return -1;
    }

    size_t payload_length = packet->length - HEADER_SIZE - CHECKSUM_SIZE;
    packet->payload = (uint8_t *)malloc(payload_length);
    if (!packet->payload) {
        fprintf(stderr, "Memory allocation failed for packet payload\n");
        return -1;
    }

    // Copy the payload data
    memcpy(packet->payload, data + HEADER_SIZE, payload_length);

    // Extract checksum from the last byte
    packet->checksum = data[data_length - 1];

    // Verify checksum
    uint8_t computed_checksum = calculate_checksum(packet->payload, payload_length);
    if (packet->checksum != computed_checksum) {
        fprintf(stderr, "Checksum validation failed\n");
        free(packet->payload);
        return -1;
    }

    return 0;  // Success
}

// Function to print a packet for debugging purposes
void print_packet(Packet *packet) {
    if (!packet) {
        return;
    }

    printf("Packet length: %u\n", packet->length);
    printf("Payload: ");
    for (size_t i = 0; i < packet->length - HEADER_SIZE - CHECKSUM_SIZE; i++) {
        printf("%02x ", packet->payload[i]);
    }
    printf("\n");
    printf("Checksum: %02x\n", packet->checksum);
}

// Function to free a packet's memory
void free_packet(Packet *packet) {
    if (packet) {
        if (packet->payload) {
            free(packet->payload);
        }
        free(packet);
    }
}

int main() {
    // Example payload data
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};

    // Create a packet
    Packet *packet = create_packet(payload, sizeof(payload));
    if (!packet) {
        return -1;  // Error creating packet
    }

    // Print the packet information
    print_packet(packet);

    // Simulate sending the packet (convert packet to raw data)
    size_t raw_packet_size = packet->length;
    uint8_t *raw_data = (uint8_t *)malloc(raw_packet_size);
    if (!raw_data) {
        free_packet(packet);
        return -1;  // Error allocating memory for raw data
    }

    // Copy the header (length) to the raw data
    raw_data[0] = (packet->length >> 24) & 0xFF;
    raw_data[1] = (packet->length >> 16) & 0xFF;
    raw_data[2] = (packet->length >> 8) & 0xFF;
    raw_data[3] = packet->length & 0xFF;
    // Copy the payload to the raw data
    memcpy(raw_data + HEADER_SIZE, packet->payload, packet->length - HEADER_SIZE - CHECKSUM_SIZE);
    // Append the checksum
    raw_data[raw_packet_size - 1] = packet->checksum;

    // Parse the packet from raw data
    Packet parsed_packet;
    if (parse_packet(raw_data, raw_packet_size, &parsed_packet) == 0) {
        printf("Packet parsed successfully\n");
        print_packet(&parsed_packet);
    } else {
        printf("Error parsing packet\n");
    }

    // Clean up
    free(raw_data);
    free_packet(packet);

    return 0;
}

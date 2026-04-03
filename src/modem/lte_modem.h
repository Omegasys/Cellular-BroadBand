#ifndef LTE_MODEM_H
#define LTE_MODEM_H

#include <stdint.h>

// Serial port configuration
#define SERIAL_PORT "/dev/ttyUSB0"  // Default serial port for the LTE modem (adjust if necessary)
#define BAUD_RATE   B115200         // Baud rate for serial communication (change as needed)

// AT Command Macros (for ease of use)
#define AT_CMD_OK       "OK"
#define AT_CMD_ERROR    "ERROR"

// LTE Modem Commands (common AT commands)
#define AT_CMD_BASIC    "AT"               // Basic AT command to check modem response
#define AT_CMD_CSQ      "AT+CSQ"           // Command to check signal quality
#define AT_CMD_CNMP     "AT+CNMP=38"       // Command to set modem to LTE mode (38 = LTE)
#define AT_CMD_CGDCONT  "AT+CGDCONT=1,\"IP\",\"internet\""  // Set PDP context (change APN as needed)
#define AT_CMD_DIAL     "ATD*99#"          // Dial command to establish a data connection

// Error Codes (optional for future implementation)
#define LTE_MODEM_SUCCESS  0
#define LTE_MODEM_ERROR    -1

// Function Prototypes
/**
 * @brief Configures the serial port for communication with the LTE modem.
 * @param fd File descriptor for the serial port.
 * @return 0 on success, -1 on failure.
 */
int configure_serial_port(int fd);

/**
 * @brief Sends an AT command to the LTE modem and waits for the response.
 * @param fd File descriptor for the serial port.
 * @param command The AT command to send to the modem.
 * @return 0 if response is received and successful, -1 on error.
 */
int send_at_command(int fd, const char *command);

/**
 * @brief Initializes the LTE modem, performs basic checks, and configures it.
 * @param fd File descriptor for the serial port.
 * @return 0 if initialization was successful, -1 on failure.
 */
int initialize_lte_modem(int fd);

/**
 * @brief Checks the signal quality of the LTE modem.
 * @param fd File descriptor for the serial port.
 * @return 0 if successful, -1 on failure.
 */
int check_signal_quality(int fd);

/**
 * @brief Sets the LTE modem to LTE mode (typically using CNMP=38).
 * @param fd File descriptor for the serial port.
 * @return 0 if successful, -1 on failure.
 */
int set_lte_mode(int fd);

/**
 * @brief Configures the APN and PDP context for data connectivity.
 * @param fd File descriptor for the serial port.
 * @param apn The Access Point Name to configure.
 * @return 0 if successful, -1 on failure.
 */
int configure_pdp_context(int fd, const char *apn);

/**
 * @brief Dials the modem to establish a data connection.
 * @param fd File descriptor for the serial port.
 * @return 0 if successful, -1 on failure.
 */
int dial_connection(int fd);

#endif // LTE_MODEM_H

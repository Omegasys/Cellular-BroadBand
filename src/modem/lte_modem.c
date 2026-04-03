#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#define SERIAL_PORT "/dev/ttyUSB0" // Modify this with your modem's serial port
#define BAUD_RATE B115200            // Set the baud rate for communication

// Function to configure the serial port
int configure_serial_port(int fd) {
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error getting term attributes");
        return -1;
    }

    cfsetospeed(&tty, BAUD_RATE);
    cfsetispeed(&tty, BAUD_RATE);

    // Set the mode (8 data bits, no parity, 1 stop bit)
    tty.c_cflag &= ~PARENB;    // No parity
    tty.c_cflag &= ~CSTOPB;    // 1 stop bit
    tty.c_cflag &= ~CSIZE;     // Mask character size bits
    tty.c_cflag |= CS8;        // 8 data bits

    // Enable receiver and set local mode
    tty.c_cflag |= CREAD | CLOCAL;

    // Disable hardware flow control (RTS/CTS)
    tty.c_cflag &= ~CRTSCTS;

    // Set raw input/output mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control

    // Set the timeout for reading from the modem
    tty.c_cc[VTIME] = 1; // 1 decisecond (0.1 second) timeout
    tty.c_cc[VMIN] = 0;  // Minimum number of characters to read

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error setting term attributes");
        return -1;
    }
    return 0;
}

// Function to send AT command to the modem
int send_at_command(int fd, const char *command) {
    write(fd, command, strlen(command));
    write(fd, "\r", 1); // Send carriage return to simulate keypress (CR)

    // Wait for a response
    usleep(500000);  // Sleep for 0.5 seconds to allow response time

    char buffer[256];
    int n = read(fd, buffer, sizeof(buffer) - 1);

    if (n < 0) {
        perror("Error reading from serial port");
        return -1;
    }

    buffer[n] = '\0'; // Null-terminate the response

    printf("Modem response: %s\n", buffer);
    return 0;
}

// Main function
int main() {
    // Open the serial port
    int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        perror("Error opening serial port");
        return -1;
    }

    // Configure the serial port
    if (configure_serial_port(fd) != 0) {
        close(fd);
        return -1;
    }

    printf("Modem connected. Initializing...\n");

    // Send AT command to check if the modem is responding
    if (send_at_command(fd, "AT") != 0) {
        close(fd);
        return -1;
    }

    // Check if the modem is registered on the network (basic LTE check)
    if (send_at_command(fd, "AT+CSQ") != 0) {
        close(fd);
        return -1;
    }

    // Set the modem to operate in LTE mode (change depending on the modem type)
    if (send_at_command(fd, "AT+CNMP=38") != 0) {  // CNMP=38 = LTE
        close(fd);
        return -1;
    }

    // Enable data mode (bearer)
    if (send_at_command(fd, "AT+CGDCONT=1,\"IP\",\"internet\"") != 0) {
        close(fd);
        return -1;
    }

    // Dial the LTE connection (this could be your APN setup)
    if (send_at_command(fd, "ATD*99#") != 0) {
        close(fd);
        return -1;
    }

    // Wait for the connection to establish (example, you can improve with timeout handling)
    printf("LTE modem connected and dialed.\n");

    // Here, you can add further interaction, such as sending/receiving data packets

    // Close the serial port
    close(fd);
    return 0;
}

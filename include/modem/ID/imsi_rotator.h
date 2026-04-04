#ifndef IMSI_ROTATOR_H
#define IMSI_ROTATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/src/modem/ID/ID.conf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/imsi_log.txt"      // Path to log file where IMSI rotation is logged

// Function prototype to read the IMSI and rotation interval from the .conf file
int read_config(char *imsi, int *rotate_interval);

// Function prototype to rotate the IMSI based on the designated time interval
void rotate_imsi(const char *imsi, const int rotate_interval);

// Function prototype to handle the IMSI rotation
void start_imsi_rotation(void);

#endif // IMSI_ROTATOR_H

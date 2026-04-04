#ifndef INZI_ROTATOR_H
#define INZI_ROTATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/src/modem/ID/ID.conf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/inzi_log.txt"     // Path to log file where INZI rotation is logged

// Function prototype to read the INZI and rotation interval from the .conf file
int read_config(char *inzi, int *rotate_interval);

// Function prototype to rotate the INZI based on the designated time interval
void rotate_inzi(const char *inzi, const int rotate_interval);

// Function prototype to handle the INZI rotation
void start_inzi_rotation(void);

#endif // INZI_ROTATOR_H

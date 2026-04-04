#ifndef AD_ID_ROTATOR_H
#define AD_ID_ROTATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_FILE_PATH "/src/modem/ID/ID.conf"  // Path to configuration file
#define LOG_FILE_PATH "/var/log/ad_id_log.txt"    // Path to log file where AD-ID rotation is logged

// Function prototype to read the AD-ID and rotation interval from the .conf file
int read_config(char *ad_id, int *rotate_interval);

// Function prototype to rotate the AD-ID based on the designated time interval
void rotate_ad_id(const char *ad_id, const int rotate_interval);

// Function prototype to handle the AD-ID rotation
void start_ad_id_rotation(void);

#endif // AD_ID_ROTATOR_H

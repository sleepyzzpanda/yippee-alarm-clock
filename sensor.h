// initializes sensor and reads from it
#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include "Generic.h"
#include "i2c.h"
#include <time.h>


void initialize_sensor(void);
double distance(void);
// returns true if needed to turn
bool turn(void);
void clean_sensor(void);

#endif
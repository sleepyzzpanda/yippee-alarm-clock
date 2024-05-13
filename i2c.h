// initializes sensor and reads from it
#ifndef I2C_H
#define I2C_H

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
#include <time.h>

void initialize_i2c();
int initI2cBus(char *bus, int address);
unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);
void clean_i2c();

#endif
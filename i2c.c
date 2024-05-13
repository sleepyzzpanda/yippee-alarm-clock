#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include "Generic.h"
#include <time.h>
#include "i2c.h"

void initialize_i2c()
{
    // configuring pins
    runCommand("config-pin P9_17 i2c");
    runCommand("config-pin P9_18 i2c");
}

int initI2cBus(char *bus, int address)
{
    // address is 0x10 for sensor

    // opens the device "/dev/i2c-1"
    int i2cFileDesc = open(bus, O_RDWR);

    // ioct sets the spi mode and speed
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
    if (result < 0)
    {
        perror("I2C: Unable to set I2C device to slave address.");
        exit(1);
    }
    return i2cFileDesc;
}

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
    // To read a register, must first write the address
    int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));
    if (res != sizeof(regAddr))
    {
        perror("I2C: Unable to write to i2c register.");
        exit(1);
    }
    // Now read the value and return it
    char value = 0;
    res = read(i2cFileDesc, &value, sizeof(value));
    if (res != sizeof(value))
    {
        perror("I2C: Unable to read from i2c register");
        exit(1);
    }
    return value;
}


void writeI2cReg(int i2cFileDesc, unsigned char regAddr,
                 unsigned char value)
{
    unsigned char buff[2];
    buff[0] = regAddr;
    buff[1] = value;
    int res = write(i2cFileDesc, buff, 2);
    if (res != 2)
    {
        perror("I2C: Unable to write i2c register.");
        exit(1);
    }
}

void clean_i2c(void)
{
    // nothing
}

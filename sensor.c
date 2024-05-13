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
#include "sensor.h"

#define I2C_DEVICE_ADDRESS 0x10
#define DISTANCE_ADDRESS 0x00

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

#define MINIMUM_DISTANCE 20

void initialize_sensor(void)
{
    // nothing
}


double distance(void)
{
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); // opening i2c file for writing
    unsigned char valSensor = readI2cReg(i2cFileDesc, DISTANCE_ADDRESS); // read from sensor
    // printf("value of sensor: %d\n",(valSensor*1));
    return valSensor * 1; // convert to double from hex
}

bool turn(void)
{
    if (distance() < MINIMUM_DISTANCE && distance() != 0) // compare val from sensor to minimum value
    {
        return 1; // return 1 (true) if you need to turn
    }

    return 0; // else return 0 no need to turn
}

void clean_sensor(void)
{
    //nothing
}

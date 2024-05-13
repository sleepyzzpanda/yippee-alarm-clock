#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include "Generic.h"
//#include <i2c.h>
#include <time.h>
#include "rtc.h"

#define I2C_DEVICE_ADDRESS 0x51
#define INIT_ADDRESS 0x0e
#define TIMER_ADDRESS 0x0f

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"

#define HZ_ENABLE 0x82
#define HZ_SAVE 0x03

bool awake = false;

void initialize_rtc(void)
{
    awake = false;
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); // opening i2c file for writing
    writeI2cReg(i2cFileDesc, INIT_ADDRESS, HZ_ENABLE); // enabling alarm and setting to 1 HZ
}

void set_timer(double timer_time)
{
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); // opening i2c file for writing
    writeI2cReg(i2cFileDesc, TIMER_ADDRESS, timer_time); // setting to given time in seconds
}

double countdown_time(void)
{
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); // opening i2c file for writing
    unsigned char valSensor = readI2cReg(i2cFileDesc, TIMER_ADDRESS); // read from sensor
    printf("value of timer: %d\n",(valSensor * 1));

    // sleep(0.7);
    return valSensor * 1; // convert to double from hex
}

bool alarm_func(void)
{
    if (countdown_time() <= 0x01 && !awake)  // compare val from countdown to time to go off
    {   sleep(1);
        awake = true;
        return 1; // return 1 (true) if you need to start alarm
    }

    return 0; // else return 0 no need to start alarm
}

void clean_rtc(void)
{
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS); // opening i2c file for writing
    writeI2cReg(i2cFileDesc, INIT_ADDRESS, HZ_SAVE); // setting to power saving mode
}

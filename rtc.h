// initializes sensor and reads from it
#ifndef RTC_H
#define RTC_H

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

// initializing i2c pins
void initialize_rtc(void);
// setting the timer time
void set_timer(double timer_time);
// reads the timer countdown time
double countdown_time(void);
// returns true if needed to turn
bool alarm_func(void);
void clean_rtc(void);

#endif
//generic functions used often: sleeping and getting time
#ifndef GENERIC_H
#define GENERIC_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#define GPIO_PATH "/sys/class/gpio/gpio51"
#define GPIO_PATH_2 "/sys/class/gpio/gpio49"

void sleepForMs(long long delayInMs);
long long getTimeInNano(void);
long long getTimeInMs(void);
void runCommand(char *command);
void export_gpio();
void set_direction(const char *direction);
void set_value(const char* value);
void set_value_axle(const char* value);
#endif
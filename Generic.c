#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include "Generic.h"

void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}

long long getTimeInNano(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long extrananoSeconds = spec.tv_nsec;
    long long nanoSeconds = seconds * 1000000 + extrananoSeconds;
    return nanoSeconds;
}

long long getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

void runCommand(char *command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe))
    {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0)
    {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}


void export_gpio(){
    runCommand("#!/bin/bash");
    runCommand("config-pin p9.16 gpio");
    runCommand("config-pin p9.23 gpio");

    // runCommand("echo 3 > /sys/class/gpio/export");
}

void set_direction(const char *direction){
    runCommand("echo out > /sys/class/gpio/gpio51/direction");
    runCommand("echo out > /sys/class/gpio/gpio49/direction");
}

void set_value(const char* value){
    char path[50];
    snprintf(path, sizeof(path), "%s/value", GPIO_PATH);

    FILE *value_file = fopen(path, "w");
    if(value_file == NULL){
        perror("error opeing valuefile");
        exit(EXIT_FAILURE);
    }

    fprintf(value_file, "%s", value);
    fclose(value_file);
}

void set_value_axle(const char* value){
    char path[50];
    snprintf(path, sizeof(path), "%s/value", GPIO_PATH_2);

    FILE *value_file = fopen(path, "w");
    if(value_file == NULL){
        perror("error opeing valuefile");
        exit(EXIT_FAILURE);
    }

    fprintf(value_file, "%s", value);
    fclose(value_file);
}




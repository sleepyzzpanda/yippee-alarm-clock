#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "UserButton.h"
#include "Generic.h"

#define EXPORT_FILE "/sys/class/gpio/export"
#define USER_BUTTON_DIRECTION_FILE "/sys/class/gpio/gpio72/direction"
#define USER_BUTTON_ACTIVELOW_FILE "/sys/class/gpio/gpio72/active_low"
#define USER_BUTTON_VALUE_FILE "/sys/class/gpio/gpio72/value"

void initialize_button(void)
{
    runCommand("config-pin p8.43 gpio");
    // runCommand("echo 72 > export");

    FILE *pUserDirectionFile = fopen(USER_BUTTON_DIRECTION_FILE, "w");
    if (pUserDirectionFile == NULL)
    {
        printf("ERROR: Unable to open User gpio72 direction file.\n");
        exit(1);
    }

    // Set User button direction file
    fprintf(pUserDirectionFile, "in");

    // Close the User Button direction file
    fclose(pUserDirectionFile);
}

int read_buttons(char *fileName)
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }

    // read string (line)
    const int MAX_LENGTH = 1024;
    char buff[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, pFile);

    // close
    fclose(pFile);
    
    return atoi(buff);
}

bool button_pressed(void)
{
    return (read_buttons(USER_BUTTON_VALUE_FILE) == 0);
}

void clean_button(void)
{
    // nothing
}
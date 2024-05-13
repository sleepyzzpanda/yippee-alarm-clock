// initializing + cleaning button and reading it
#ifndef USERBUTTON_H
#define USERBUTTON_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

void initialize_button(void);
void clean_button(void);
void runCommand(char *command);
int read_buttons(char *fileName);
bool button_pressed(void);

#endif
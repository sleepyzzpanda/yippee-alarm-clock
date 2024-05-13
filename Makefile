#makefile for sensor
SRC_C = sensor.c Generic.c UserButton.c i2c.c rtc.c

PUBDIR = $(HOME)/cmpt433/public/myApps
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -static -g -std=c99 -D _POSIX_C_SOURCE=200809L -g -Werror

all: sensor

sensor:
	$(CC_C) $(CFLAGS) servo_test.c $(SRC_C) -o $(PUBDIR)/project -lpthread -lm

clean:
	rm -f $(OUTPUTS)/project
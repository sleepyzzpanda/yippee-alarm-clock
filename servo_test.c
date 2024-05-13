#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "Generic.h"
#include "i2c.h"
#include "sensor.h"
#include "UserButton.h"
#include "rtc.h"

int main(){
    // wakeywakey = true;
    // turning = false;
    initialize_i2c();
    initialize_rtc();
    initialize_sensor();
    initialize_button();
    export_gpio();
    set_direction("out");
    
    set_timer(5);
    // printf("timer set\n");
    // // ----- testing fork() ---------
    pid_t pid, pid2;

    // rtc
    while(1){
        sleep(0.05);
        if(alarm_func()){ 
            printf("awake\n");
            break;

        }
        sleep(1);
    }

    // pid = fork();
    // if(pid < 0 ){
    //     return 1;
    // } else if (pid == 0){
    //     // // child 0
        // // audio
        pid2 = fork();
        if(pid2 < 0){
            return 1;
        } else if(pid2 == 0){
            // child
            //motor
            while(!button_pressed()){
                //motor
                // sensor?
                sleepForMs(50);
                //printf("hi\n");
                if(!turn()){
                    set_value("1");  
                    set_value_axle("1");    
                    sleep(0.01);
                    set_value("0");
                    set_value_axle("0");
                    sleep(0.1);
                } else {
                    // go backwards
                    printf("need to turn\n");
                    for(int i = 0; i < 200; i++){
                        set_value("1");
                        set_value_axle("1");
                        sleepForMs(2);
                        set_value("0");
                        set_value_axle("0");
                        sleepForMs(20);
                    }
                }
            }
            return 0;
        } else{
            // audio
           while(!button_pressed()){
               runCommand("aplay whistle.wav");
           }
            // return 0;

        }
        
    // } else {
    //     // parent 0
    //     // return 0;
    // }

    printf("exiting\n");
    return 0; 
}

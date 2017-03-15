/*
 * File:   main.c
 * Author: cumbel
 *
 * Created on March 14, 2017, 8:13 PM
 */

#include <xc.h>
#include <pic18f2550.h>
#include <plib/timers.h>
#include "hardware_configuration.h"
#include "logging.h"
#include "control.h"
#include "itoa.h"
#include "motor.h"

#define BOUND_LEFT      4500
#define BOUND_RIGHT     4300
#define BOUND_FORWARD   4400


void main(void) {
    OSCCON = 0b01110000;
    CMCON = 7;

    LOG_INIT();
    LOG_LN("Starting");
    control_init();
    LOG_LN("Control initialized");
    motor_init();
    LOG_LN("Motors initialized");
    
    while (1) {
        LOG_LN("=======");        

        int x = control_read_x();
        int y = control_read_y();
        
        int horiz_dir = 0;
        int virt_dir = 0;
        
        if(x < BOUND_RIGHT) {
            horiz_dir = MOTOR_DIRECTION_RIGHT;
        } else if(x > BOUND_LEFT) {
            horiz_dir = MOTOR_DIRECTION_LEFT;            
        }
        
        if(y < BOUND_FORWARD) {
            virt_dir = MOTOR_DIRECTION_FORWARD;
        }        
 
#ifdef __DEBUG
        char message[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
        log_message("x: ");        
        itoa(x, message);        
        LOG_LN(message);
        log_message("y: ");                
        itoa(y, message);        
        LOG_LN(message);
#endif
        
        motor_set_direction(virt_dir | horiz_dir);
    }    
}

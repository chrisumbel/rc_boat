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

void main(void) {
    OSCCON = 0b01110000;
    CMCON = 7;

    log_init();
    log_message_ln("Starting");
    control_init();
    log_message_ln("Control initialized");
    motor_init();
    log_message_ln("Motors initialized");
    
    while (1) {
        for(int i = 0; i < 100; i++) {
            __delay_ms(10);
        }

        char message[16];
        log_message_ln("=======");        

        control_read_x(); // clean
        int x = control_read_x();

        control_read_y(); // clean        
        int y = control_read_y();
        
        int horiz_dir = 0;
        int virt_dir = 0;
        
        if(x < 4300) {
            horiz_dir = MOTOR_DIRECTION_RIGHT;
        } else if(x > 4500) {
            horiz_dir = MOTOR_DIRECTION_LEFT;            
        }
        
        if(y < 4400) {
            virt_dir = MOTOR_DIRECTION_FORWARD;
        }        
        
        log_message("x: ");        
        itoa(x, message);        
        log_message_ln(message);
        log_message("y: ");                
        itoa(y, message);        
        log_message_ln(message);
        
        motor_set_direction(virt_dir | horiz_dir);
    }    
}

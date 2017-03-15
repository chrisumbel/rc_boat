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

void main(void) {
    OSCCON = 0b01110000;
    CMCON = 7;

    log_init();
    log_message_ln("Starting");
    control_init();
    log_message_ln("Control initialized");

    while (1) {
        char message[16];
        log_message_ln("=======");        
        int x = control_read_x();
        int y = control_read_y();
        
        log_message("x: ");        
        itoa(x, message);        
        log_message_ln(message);
        log_message("y: ");                
        itoa(y, message);        
        log_message_ln(message);
    }    
}

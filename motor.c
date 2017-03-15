
#include <pic18f2550.h>

#include "motor.h"

int motor_init() {
    TRISB0 = 0;
    TRISB1 = 0;    
    TRISB2 = 0;       
    AN0 = 0;
    AN1 = 0;
    AN2 = 0;    
}

int motor_set_direction(int direction) {
    LATB &= 0b11111000;
    LATB |= direction;    
}

#include "control.h"
#include <plib/capture.h>
#include <plib/timers.h>

int control_init() {
    TRISC1 = 1; 
    TRISC2 = 1; 
    
    return 0;
}


int read_ccp2(unsigned char config) {
    OpenCapture2(config & CAPTURE_INT_ON);    

    OpenTimer1(TIMER_INT_OFF & T1_SOURCE_INT & T1_SOURCE_CCP);
    PIR2bits.CCP2IF = 0;     
    
    while(PIR2bits.CCP2IF == 0);  // Wait for event
  
    int d = ReadCapture2();

    PIR2bits.CCP2IF = 0;

    CloseCapture2();
    CloseTimer1();  
    
    return d;
}

int read_ccp1(unsigned char config) {
    OpenCapture1(config & CAPTURE_INT_ON & T1_SOURCE_CCP);    

    OpenTimer1(TIMER_INT_OFF & T1_SOURCE_INT);
    PIR1bits.CCP1IF = 0; 
    
    while(PIR1bits.CCP1IF == 0);  // Wait for event
  
    int d = ReadCapture1();

    PIR1bits.CCP1IF = 0;

    CloseCapture1();    
    CloseTimer1();
    
    return d;
}

int control_read_x() {
    PIR1bits.CCP1IF = 0; 
    
    SetTmrCCPSrc(T1_SOURCE_CCP);
    int s = read_ccp1(CAP_EVERY_RISE_EDGE);
    int e = read_ccp1(CAP_EVERY_FALL_EDGE);
    
    return s - e;
}

int control_read_y() {
    PIR2bits.CCP2IF = 0; 
    
    SetTmrCCPSrc(T1_SOURCE_CCP);
    int s = read_ccp2(CAP_EVERY_RISE_EDGE);
    int e = read_ccp2(CAP_EVERY_FALL_EDGE);
    
    return s - e;
}
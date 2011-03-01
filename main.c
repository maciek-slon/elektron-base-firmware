/*
 * File:   main.c
 * Author: konrad
 *
 * Created on 26 luty 2011, 11:14
 */

#include <p33Fxxxx.h>

#include "qei.h"
#include "uart.h"
#include "pwm.h"
#include "control.h"

_FOSC( FCKSM_CSECME & OSCIOFNC_ON & POSCMD_NONE & IOL1WAY_OFF );
_FWDT( FWDTEN_OFF );


void initIO() {

}

void initClock() {
    PLLFBD = 41; // M = 40
    CLKDIVbits.PLLPOST = 0; // N1 = 2
    CLKDIVbits.PLLPRE = 0; // N2 = 2
    OSCTUN = 0;
    RCONbits.SWDTEN = 0;

    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x01); // Initiate Clock Switch to
    // FRC with PLL (NOSC=0b001)
    __builtin_write_OSCCONL(0x01); // Start clock switching

    // disable two next lines when emulating in proteus VMS
    while (OSCCONbits.COSC != 0b001); // Wait for Clock switch to occur
    while (OSCCONbits.LOCK != 1) {
    };
}

int main(void) {
    initClock();
    initIO();
    initQEI();
    initUART();
    initPWM();
    initControl();
    initTIMER();

    while(1);
    
    return 0;
}

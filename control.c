#include <p33Fxxxx.h>
#include "control.h"
#include "qei.h"
#include "pwm.h"
#include "config.h"
#include <dsp.h>

// Global variables
int speed1 = 0;
int speed2 = 0;

int tspeed1 = 0;
int tspeed2 = 0;

tPID pid1;
tPID pid2;

// Local variables
int lpos1 = 0;
int lpos2 = 0;

char mode1 = 1;
char status1 = 0;

char mode2 = 0;
char status2 = 0;

fractional abcCoefficient1[3] __attribute__((section(".xbss, bss, xmemory")));
fractional controlHistory1[3] __attribute__((section(".ybss, bss, ymemory")));

fractional abcCoefficient2[3] __attribute__((section(".xbss, bss, xmemory")));
fractional controlHistory2[3] __attribute__((section(".ybss, bss, ymemory")));

int speedbuf1[10];
int speedbuf2[10];
int spi = 0;

//--------------

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {

    int pos;
    int i;

    // ---------------------------------------
    pos = GetPos1();
    pos += 4 * ENCRES * GetIndex1();

    speedbuf1[spi] = pos - lpos1;
    lpos1 = pos;

    speed1 = 0;

    for (i = 0; i < 10; i++)
        speed1 += speedbuf1[i];

    pid1.measuredOutput = speed1;
    pid1.controlReference = tspeed1;

    PID(&pid1);

    setPWM1(pid1.controlOutput);

    // -------------------------------------

    pos = GetPos2();
    pos += 4 * ENCRES * GetIndex2();

    speedbuf2[spi] = pos - lpos2;
    lpos2 = pos;
    spi++;
    if (spi > 9)
        spi = 0;

    speed2 = 0;
    for (i = 0; i < 10; i++)
        speed2 += speedbuf2[i];

    pid2.measuredOutput = speed2;
    pid2.controlReference = tspeed2;

    PID(&pid2);

    setPWM2(pid2.controlOutput);

    IFS0bits.T1IF = 0; //Clear Timer1 interrupt flag
}

void initControl() {
    
    fractional kCoeffs[3];

    kCoeffs[0] = Q15(0.9);
    kCoeffs[1] = Q15(0.8);
    kCoeffs[2] = Q15(0.00);

    pid1.abcCoefficients = &abcCoefficient1[0]; /*Set up pointer to derived coefficients */
    pid1.controlHistory = &controlHistory1[0]; /*Set up pointer to controller history samples */

    pid2.abcCoefficients = &abcCoefficient2[0]; /*Set up pointer to derived coefficients */
    pid2.controlHistory = &controlHistory2[0];

    PIDInit(&pid1);
    PIDInit(&pid2);

    PIDCoeffCalc(&kCoeffs[0], &pid1);
    PIDCoeffCalc(&kCoeffs[0], &pid2);

}

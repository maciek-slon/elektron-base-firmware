#include <p33Fxxxx.h>

#include <dsp.h>

#include	"serial.h"
#include	"qei.h"
#include	"pwm.h"
#include	"uart.h"
#include	"control.h"

// External global variables
extern struct tPID pid1;
extern struct tPID pid2;

extern int pos1;
extern int pos2;

extern int speed1;
extern int speed2;

extern int tspeed1;
extern int tspeed2;

// Local variables
union packet pack;

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {

    fractional kCoeffs[3];
    char c;
    c = U1RXREG;
    if (c == START_BYTE) {
        readUART1(&c, 1);
        switch (c) {
            case SPEAD_CMD:
                readUART1((char*) &pack, sizeof (struct sersetspead));
                tspeed1 = pack.setspead.spead1;
                tspeed2 = pack.setspead.spead2;

                pack.getpos.index1 = pos1;
                pack.getpos.pos1 = POS1CNT;
                pack.getpos.index2 = pos2;
                pack.getpos.pos2 = POS2CNT;
                pack.getpos.spead1 = speed1;
                pack.getpos.spead2 = speed2;
                writeUART1((char*) &pack, sizeof (struct sergetpos));
                break;
            case PID_CMD:

                readUART1((char*) &pack, sizeof (struct sersetpid));
                kCoeffs[0] = pack.setpid.p1;
                kCoeffs[1] = pack.setpid.i1;
                kCoeffs[2] = pack.setpid.d1;
                PIDCoeffCalc(&kCoeffs[0], &pid1);

                kCoeffs[0] = pack.setpid.p2;
                kCoeffs[1] = pack.setpid.i2;
                kCoeffs[2] = pack.setpid.d2;
                PIDCoeffCalc(&kCoeffs[0], &pid2);
                break;
        };

    }
    IFS0bits.U1RXIF = 0;
}

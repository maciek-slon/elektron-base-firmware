#include <p33Fxxxx.h>

#include "inttypes.h"

#include "config.h"

#ifdef ENCx4
#define MAXCNT ENCRES * 4
#else
#define MAXCNT ENCRES * 2
#endif

int16_t pos1 = 0;
int16_t pos2 = 0;

void __attribute__((interrupt, no_auto_psv)) _QEI1Interrupt(void) {
    if (QEI1CONbits.UPDN == 1) {
        pos1++;
    } else {
        pos1--;
    }
    IFS3bits.QEI1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _QEI2Interrupt(void) {
    if (QEI2CONbits.UPDN == 1) {
        pos2++;
    } else {
        pos2--;
    }
    IFS4bits.QEI2IF = 0;
}

void initQEI() {
    // QEI1
    QEI1CONbits.POSRES = 1;
    QEI1CONbits.PCDOUT = 0;
    QEI1CONbits.SWPAB = 0;

    QEI1CONbits.UPDN = 0;
    QEI1CONbits.QEISIDL = 0;
    QEI1CONbits.CNTERR = 0;

    DFLT1CONbits.QECK = 0;
    DFLT1CONbits.QEOUT = 0;
    DFLT1CONbits.CEID = 1;

    MAX1CNT = MAXCNT;

#ifdef ENCx4
    QEI1CONbits.QEIM = 7;
#else
    QEI1CONbits.QEIM = 4;
#endif

    IFS3bits.QEI1IF = 0;
    IEC3bits.QEI1IE = 1;

    // QEI2
    QEI2CONbits.POSRES = 1;
    QEI2CONbits.PCDOUT = 0;
    QEI2CONbits.SWPAB = 0;

    QEI2CONbits.UPDN = 0;
    QEI2CONbits.QEISIDL = 0;
    QEI2CONbits.CNTERR = 0;

    DFLT2CONbits.QECK = 0;
    DFLT2CONbits.QEOUT = 0;
    DFLT2CONbits.CEID = 1;

    MAX2CNT = MAXCNT;

#ifdef ENCx4
    QEI2CONbits.QEIM = 7;
#else
    QEI2CONbits.QEIM = 4;
#endif

    IFS4bits.QEI2IF = 0;
    IEC4bits.QEI2IE = 1;

}

int GetIndex1() {
    return pos1;
}

unsigned int GetPos1() {
    return POS1CNT;
}

int GetIndex2() {
    return pos2;
}

unsigned int GetPos2() {
    return POS2CNT;
}

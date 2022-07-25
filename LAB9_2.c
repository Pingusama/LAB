#include <xc.h>
#include "config.h"


//function prototypes declaration:
void initSysPins(void);
void initSysDevices(void);
void __interrupt() isr(void);

void main(void)
{
    initSysPins();
    initSysDevices();
    
    PORTA = 0b00000010;
    while(1)
    {
        //do nothing
    }
}

void initSysPins(void)
{
    ANSELA = 0x00;
    TRISA = 0xFC;
}

void initSysDevices(void)
{
    INTCONbits.GIE = 0;
    T0CON0 = 0b10010000;
    T0CON1 = 0b01000100;
    TMR0H = 0x0B;
    TMR0L = 0xDC;
    PIR0bits.TMR0IF = 0;
    PIE0bits.TMR0IE =1;
    INTCONbits.GIE =1;
}


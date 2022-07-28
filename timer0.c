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
    // disable all active interrupts
    INTCONbits.GIE = 0;
    // enable the timer0 and set the postscaler to 1:5
    T0CON0 = 0b10000100;
    // set the timer0 with synchronize mode and use the system oscillator (FOSC/4) as the clock source
    // set the prescale rate to 1:4
    T0CON1 = 0b01000010;
    // leave it for now
    TMR0H = 249;
    // reset TMR0 Overflow Interrupt Flag bit
    PIR0bits.TMR0IF = 0;
    // enable the TMR0 Overflow Interrupt 
    PIE0bits.TMR0IE =1;
    // enable all active interrupts
    INTCONbits.GIE =1;
}

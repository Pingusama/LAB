#include <xc.h> 
#include "config.h"

void initSysPins(void);
void initSysDevices(void);
void __interrupt()isr(void);

void main(void)
{
    initSysPins();
    initSysDevices();
    
    while(1)
    {
        if(PORTBbits.RB0 == 0)
        {
            __delay_ms(50);
            if(PORTBbits.RB0 == 0)
            {
                while(PORTBbits.RB0 == 0);
                PORTAbits.RA0 = 1;
                __delay_ms(5000);
                PORTAbits.RA0 = 0;
                
                    
            }
        }
    }
}

void initSysPins(void)
{
    ANSELA = 0x00;
    ANSELB = 0b00000000;
    TRISA = 0xFC;
    TRISB = 0b11111111;
    
}

void initSysDevices(void)
{
    INTCONbits.GIE = 0;
    PIR0bits.INTF = 0;
    INTPPS = 0x09;
    INTCONbits.INTEDG = 1;
    PIE0bits.INTE = 1;
    INTCONbits.GIE = 1;
    
}

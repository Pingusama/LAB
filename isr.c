#include <xc.h>
#include "config.h"


void __interrupt() isr(void)
{
    if(PIR0bits.TMR0IF == 1)
    {
        PIR0bits.TMR0IF = 0;
        // PORTAbits.RA0 = ~PORTAbits.RA0;
        // PORTAbits.RA1 = ~PORTAbits.RA1;
        
    }
}

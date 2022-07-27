#include <xc.h>
#include "config.h"


void shiftPortALEDs(void)
{
    int cnt;
    PORTA = 0b00001000;
    for(cnt=0; cnt<3; cnt++)
    {
        __delay_ms(1000);
        PORTA = PORTA >> 1;
    }
}

void togglePortALEDs(void)
{
    unsigned char cnt;
    
    LATA = 0x0F; // ON all LED
    for(cnt = 0; cnt <10; cnt++)
        
    {
        PORTA = ~LATA;
        __delay_ms(500); //delay
        
    }
    PORTA = 0x00; // OFF all LED
       
}


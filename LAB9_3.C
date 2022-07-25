#include <xc.h>
#include "config.h"

//function declaration
void initSysPins(void);
unsigned char detSW1(void);

void main(void)
{
    unsigned int cnt;
    
    initSysPins();
    
    while(1)
    {
        if(detSW1() == 1)
        {
            for(cnt = 0; cnt < 1000; cnt++)   //produce 1 kHz tone for 1 sec
            {
                BUZZER = 1;
                __delay_us(500);
                BUZZER = 0;
                __delay_us(500);
            }
        }
    }
}

void initSysPins(void)
{
    ANSELB = 0x00;
    TRISB = 0xF7;
}

unsigned char detSW1(void)
{
    int detect = 0;
    
    if(SW1 == 0)
    {
        detect = 1;
        while(SW1 == 0);
        
        
     
        
    }
    return detect;
    
}

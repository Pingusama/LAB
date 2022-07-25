#include <xc.h>
#include "config.h"

void initSysPins(void);
void shiftLEDs(void);


void main(void) 
{
    initSysPins();
    
    PORTA = 0x00;
   
    while(1)
    {
        shiftLEDs(); //function call
    }
}

//function definition

void initSysPins(void)
{
    ANSELA = 0b00000000;
    TRISA = 0b11110000;
    
    
}

void shiftLEDs(void)
{
    int cnt;
    PORTA = 0b00001000;
    for(cnt=0; cnt<3; cnt++)
    {
  
        __delay_ms(1000);
        PORTA = PORTA >> 1;
       
    }
     
   
    
   
}

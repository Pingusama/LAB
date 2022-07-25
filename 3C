#include <xc.h>
#include "config.h"
void initSysPins(void);
void shiftLEDs(void);

void main(void) 

{
    initSysPins();
    
     //function call
    
    //initialise the I/O Port
   
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
    PORTA = 0x00; //write the value of 0x00 to PORTA - SEQ1
    __delay_ms(1000);
    
    PORTA = 0x08;
    __delay_ms(1000);
    
    PORTA = 0x04;
    __delay_ms(1000);
    
    PORTA = 0x02;
    __delay_ms(1000);
   
    PORTA = 0x01;
    __delay_ms(1000);
}

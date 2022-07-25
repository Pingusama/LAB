#include <xc.h>
#include "config.h"

//function Declarations
void initSysPins(void);
void toggleLEDs(void);

void main(void) {
   
    initSysPins(); //Configure the I/O port
   
    PORTA = 0x0A;    //light up LED1 and LED3
    
    while(1)         //check if SW1 is pressed
    {
        if(PORTBbits.RB0 == 0)  //if yes
        {
            toggleLEDs(); //blink the LEDs 5 times
        }
        
       }
}
    
void initSysPins(void)
{
    ANSELA = 0b00000000;
    TRISA = 0b11110000;
    ANSELB = 0x00;
    TRISB = 0xFF;
}
void toggleLEDs(void)

{
    unsigned char cnt;
    
    PORTA = 0x00;
    
    for(cnt = 0; cnt <10; cnt++)
        
    {
        PORTA = PORTA ^ 0x0F;
        __delay_ms(500);
        
    }
  
       
}

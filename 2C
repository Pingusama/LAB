#include <xc.h>
#include "config.h"
// Function Declarations:
void initSysPins(void);
void blinkALLLEDs(void);
void onLED1n3(void);

void main(void)
{
 initSysPins(); // Configure I/O pins
 while(1)
 {
     if(PORTBbits.RB1 == 0 && PORTBbits.RB2 == 1)
         blinkALLLEDs();
     else if(PORTBbits.RB1 == 1 && PORTBbits.RB2 == 0)
         onLED1n3();
 }
}
void initSysPins(void)
{
 ANSELA = 0; 
 ANSELB = 0; 
 TRISA = 0b11110000;
 TRISB = 0b11111111; 
}
void blinkALLLEDs(void)
{
    PORTA = 0b11111111; //turn on all LEDs
    __delay_ms(1000);
    PORTA = 0b11110000; //turn off all LEDs
    __delay_ms(1000);
}
void onLED1n3(void)
{
    PORTA = 0b00000101; //0x05
}

#include <xc.h>
#include "config.h"

//Function prototypes
void initSysPins(void);
unsigned char getNumber(void);
void blinkallLEDs(void);
void onLED1_3Sec(void);

void main(void)
{
    unsigned char cnt, num; //variable declaration
    initSysPins();
    PORTA = 0b00000000;
    while(1)
    {
        
        num = getNumber();
        for(cnt = 0; cnt<num; cnt++)
        { 
            blinkallLEDs();
         
        }
        onLED1_3Sec();
            
    }
}

void initSysPins(void)
{
    ANSELA = 0x00;
    TRISA = 0b11110000;  //output
    ANSELB = 0x00;
    TRISB = 0xFF; //input
   
}

void blinkallLEDs(void)
{
    PORTA = 0x00;
    __delay_ms(500);
    PORTA = 0x0F;
    __delay_ms(500);
    
}


unsigned char getNumber(void)
{
    unsigned char input;
    input = PORTB & 0b00000110;
    input = input >> 1;
    
    return (input);
    
}
void onLED1_3Sec(void)
{
    PORTA = 0b00000001;  //Turn on LED1
     __delay_ms(3000);
    PORTA = 0b00000000;  //Turn off LED1
    
          
}

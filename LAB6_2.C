#include <xc.h>
#include "config.h"
#define SW1 PORTBbits.RB0

void initSysPins(void);
void disp7seg(void);
int detSW1(void);

unsigned char dig1, dig0, dig2, dig3;

void main(void)
{
    int count = 0;
    initSysPins();
    while(1)
    {
        if (detSW1() == 1)
        {
            count++;
            if (count >9999)
                count = 0;
        }
        dig3 = (count/1000);  //thousand
        dig2= (count/100)%10; //hundred
        dig1= ((count/10)%10); //calculate dig1, tenth
        dig0= count%10; //calculate dig0, unit
        disp7seg(); //call function to allow seven segment units to be displayed
    }
}
void initSysPins(void)
{
    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    TRISA=0b11000000;
    TRISB=0b11111111;
    TRISC=0b00000000;
}
int detSW1(void) //specify the return type
{
    unsigned char detect = 0;
    if(SW1 ==0)
    {
        __delay_ms(50);
        if (SW1 == 0)
        {
            detect = 1;
            while (SW1 ==0);
        }
    }
    return detect;
}
const unsigned char segTable[]=
{
    0b11000000,
    0b11111001,
    0b10100100,
    0b10110000,
    0b10011001,
    0b10010010,
    0b10000010,
    0b11111000,
    0b10000000,
    0b10011000,
    0b11111111
};
void disp7seg(void)
{
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC=segTable[dig0]; //display on right most digit of display
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 =1;
    PORTC=segTable[dig1];
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5 = 1; //this selects the hundred digi 7 seg
    PORTAbits.RA4 =0;
    PORTC=segTable[dig2];
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5 = 1; //this selects the thousand digi 7 seg
    PORTAbits.RA4 =1;
    PORTC=segTable[dig3];
    __delay_ms(5);
    PORTC=segTable[10];
}

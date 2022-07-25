#include <xc.h>
#include "config.h"

void initADC(void)
{
    ADREF = 0b00000000; //Set VREF+ and VREF- to VSS and VDD
    ADCLK = 0b00000011; //Set TAD = 2us
    ADACQ = 0b00000000; //TACQ to be manually inserted
    ADCON0 = 0b10000000; //Enable ADC, single conversion, FOSC clk,
                         //result is left justified
}
unsigned char readPot(void)
{
    unsigned char result;
    ADPCH = 0b00000000; //select channel ANA0 for input at RA0
    __delay_us(5);
    ADCON0bits.ADGO = 1; //start conversion
    while(ADCON0bits.ADGO == 1); //wait for conversion to be done
    
    //result = ADRESL + ADRESH*256;
    result = ADRESH & 0b11100000;
    result = result >> 4;
    
    return result;
    
    
}

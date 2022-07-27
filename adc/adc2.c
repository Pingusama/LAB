#include <xc.h>
#include "config.h"
// Function to initialise the ADC
void initADC(void)
{
ADREF = 0x00; // Set VREF+ and VREF- to VSS and VDD
ADCLK = 0x03; // Set TAD = 2 us
ADACQ = 0x00; // TACQ to be manually inserted
ADCON0 = 0x84; // Enable ADC, single conversion, FOSC clk,
// result is left justified
}

// Function to start ADC conversion and get the results
unsigned int readPot(void)
{
 unsigned int result;

 ADPCH = 0x00; // Select channel ANA0 for input at RA0
 __delay_us(5); // Add 5 us TACQ manually
 ADCON0bits.ADGO = 1; // Start conversion
 while(ADCON0bits.ADGO == 1);
 result = ADRESH*256 + ADRESL; 

 return (result); // Return the result
}

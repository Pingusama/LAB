#include <xc.h>
#include "config.h"
// Function Declarations:
void initSysPins(void);
void onLED(void);
void offLED(void);

void main(void)
{
 initSysPins(); // Configure I/O pins
 while(1)
 { 
 if(PORTBbits.RB0 == 0) // Is SW1 pressed?
 onLED(); // Turn on LED
 else
 offLED(); // Turn off LED
 }
}
void initSysPins(void)
{
 ANSELA = 0b00000000; // RA0 as digital I/O
 ANSELB = 0; // RB0 as digital I/O
 TRISA = 0b1111110; // RA0 is output
 TRISB = 1; // RB0 is input
}
void onLED(void)
{
 PORTAbits.RA0 = 1; // Turn on LED
}
void offLED(void)
{
 PORTAbits.RA0 = 0; // Turn off LED
}

#include <xc.h>
#include "config.h" // Include the header file
void initSysPins(void);
void initLCD(void);
void lcdWriteData(char); // Declare lcdWriteData() function
void main(void) {
 char message[] = "yes!"; // Declare the string
 unsigned char i;

 initSysPins(); // Initialise the ports
 initLCD(); // Initialise the LCD module

 for(i = 0; message[i] != 0; i++) {
 lcdWriteData(message[i]); // Display one character
 }

 PORTA = 0b11110000; // Turn off the 4 LEDs first
while(1) {
 PORTA = ~PORTA; // Toggle the LEDs so that
 __delay_ms(1000); // we know the program is running
}
}
void initSysPins(void)
{
    ANSELA = 0;
    ANSELD = 0;
    ANSELE = 0;
    TRISA = 0b11110000;
    TRISD = 0x0F;   //RD4,5,6,7 are outputs
    TRISE = 0b11111100; //
}

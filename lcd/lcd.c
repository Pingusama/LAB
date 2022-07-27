#include <xc.h>
#include "config.h" // Include header file

#define LCD_DATA PORTD // Port used by LCD
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0 // E signal for LCD

void initLCD(void);
void lcdWriteCtrl(char);
void lcdWriteData(char);
void lcdSetPos(unsigned char row, unsigned char col);

// Function to initialise LCD
void initLCD()
{
    // Special Sequence a) to d) required for 4-bit interface
    __delay_ms(15); // a) 15ms LCD power-up delay
    lcdWriteCtrl(0b00000011); // b) Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5); // c) 5ms delay
    lcdWriteCtrl(0b00000010); // d) Function Set (DB4-DB7:4-bit interface)
    lcdWriteCtrl(0b00101000); // Function Set - 4-bit, 2 lines, 5x7
    lcdWriteCtrl(0b00001100); // Display on, cursor off
    lcdWriteCtrl(0b00000110); // Entry mode - inc addr, no shift
    lcdWriteCtrl(0b00000001); // Clear display & home position
}

// Function to write control instruction, 4-bit at a time
void lcdWriteCtrl(char x)
{
    LCD_RS = 0;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x<<4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}
// Function to write data, 4-bit at a time
void lcdWriteData(char x)
{
    LCD_RS = 1;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x<<4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}

void lcdSetPosition(unsigned char r, unsigned char c)
{
    unsigned char ramAddr; // Ctrl instruction to be sent
    if(r == 1) // If row is 1:
    ramAddr = 0x00 + c - 1; // Subtract 1 from the col
    else // If row is 2:
    ramAddr = 0x40 + c - 1; // Add 0x40 to ramAddr, and
    // subtract 1 from the col
    lcdWriteCtrl(ramAddr + 0x80); // Add 0x80 to ramAddr and write
    // ctrl instruction
}


void lcdWriteMessage (char message [],unsigned char row)
{
    unsigned char i;
    lcdSetPosition (1,1);
    for (i=0; message[i] !=0; i++)
    {
        lcdWriteData(message[i]);
    }
}

void lcdClearDisplay(void)
{
    lcdWriteCtrl(0b00000001); // Clear display & home position
}
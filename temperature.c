#include <xc.h>
#include "gsdf.h"
#define TRUE 1
#define FALSE 0
#define S4 PORTAbits.RA4
//#define convertRawToCelsius (5*100)/128
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0 
#define LCD_DATA PORTD
unsigned int result;
unsigned char digitM, digitC, digitX, digit;

void initSysPins(void);
void initLCD(void);
void initADC(void);
void initSysDev(void);
//void initSysDev2(void);
void __interrupt() isr(void);
//void __interrupt() isr2(void);
void lcdWriteCtrl(char);
void lcdWriteData(char);
void lcdClearDisplay(void);
void lcdSetPosition(unsigned char r, unsigned char c );
void lcdWriteMessage(char message[ ], unsigned char r);
void tempchange(void);


unsigned char getKey(void);
void showKeys(void);
void showTemp35(void);

void main(void) 
{ 
	unsigned char i, key;
    	int loop = TRUE;
   
	initSysPins();
    initADC();
    initSysDev();
    //initSysDev2();
	initLCD(); 
	while (loop) 
	{ 
       lcdClearDisplay();
       lcdWriteMessage("Press 1 or 2",1);
       lcdWriteMessage("(1) Temp (2) Keypad",2);
       while ((key=getKey())==0); // wait for key entry
       switch(key)
       	      {
           		case '1':
               		initADC();
               		showTemp35();
               		break;
           		case '2':
               		showKeys();
               		break;
           	default : 
               lcdClearDisplay();
               lcdWriteMessage("Invalid option",2);
       	}
       	while ((key=getKey())==0); // wait for key entry
    	}
}

void showTemp35(void)
{
    
    
    unsigned char key;
    int demo = TRUE;
    char res[20];
    float fres;
    lcdWriteCtrl(0b00000001);
    while(demo)
    {
        ADPCH = 0b00000000;
        __delay_us(5);
        ADCON0bits.ADGO = 1;
        while(ADCON0bits.ADGO ==1);
        result = ADRESH*256+ADRESL;
        result = result*3;
        //result = result*convertRawToCelsius;
        digitM=(unsigned char)(result/1000);
        digitC=(unsigned char)((result%1000)/100);
        digitX=(unsigned char)((result%100)/10);
        digit= (unsigned char)(result%10);
        lcdSetPosition(1,1);
        lcdWriteMessage("Temp read = ",1);
        lcdWriteData(digitM+0x30);
        lcdWriteData(digitC+0x30);
        lcdWriteData(digitX+0x30);
        tempchange();
        if (S4==1)
            demo=FALSE;
    }
}

void showKeys(void)
{
    int demo = TRUE;
    unsigned char i, key;
    
    lcdClearDisplay();
    i=0;
    while(demo)
    {
        while((key=getKey())==0);
        lcdWriteData(key);
        i++;
                if (i==16)
                {
                    i=0;
                    lcdClearDisplay();
                }
        __delay_ms(200);
        if(S4 == 1)
        {
            demo= FALSE;
        }
    }
}
void initSysPins()
{
    ANSELA=0b00000001;
    ANSELB=0;
    ANSELC=0b00000000;
    ANSELD=0b00000001;
    ANSELE=0b00000000;
    TRISA=0b11110001;
    TRISB=0xFF;
    TRISC=0xFF;
    TRISD=0x0F;
    TRISE=0b11111100;
            
}

void initADC(void)
{
    ADREF = 0b00000000;
    ADCLK = 0b00000011;
    ADACQ = 0b00000000;
    ADCON0 = 0b10000100;
}

void initSysDev(void)
{
    INTCONbits.GIE=0;
    PIR0bits.INTF=0;
    INTPPS=0x01;
    INTCONbits.INTEDG =1;
    PIE0bits.INTE=1;
    INTCONbits.GIE=1;
}
/*void initSysDev2(void)
{
    INTCONbits.GIE=0;
    PIR0bits.INTF=0;
    INTPPS=0x02;
    INTCONbits.INTEDG=1;
    PIE0bits.INTE=1;
    INTCONbits.GIE=1;
}*/
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

void tempchange(void)
{
    if(digitC >= 4)
        {
            PORTAbits.RA1=1;
        }
    else if(digitC<=1)
        {
            PORTAbits.RA2=1;
            PORTAbits.RA5=1;
        }
    else
        {
            PORTA=0x00;
        }
}

#include <xc.h>
#include "gsdf.h"
#include "lcd.h"
#include "humidity.h"
#include "keys.h"

#define TRUE 1
#define FALSE 0
#define S4 PORTAbits.RA4
//#define convertRawToCelsius (5*100)/128
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0 
#define LCD_DATA PORTD

unsigned int result;
unsigned char digitM, digitC, digitX, digit;



static void initSysPins(void);
static void initADC(void);
static void initSysDev(void);


//void initSysDev2(void);
void __interrupt() isr(void);
//void __interrupt() isr2(void);



void main(void) 
{ 
	unsigned char i, key;
    unsigned int temp;
    unsigned int humidity;
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
       lcdWriteMessage("(1) Temp (2) Keypad" ,2);
       while ((key=getKey())==0); // wait for key entry
       switch(key)
       	      {
           		case '1':
                    bool demo = TRUE;
               		initADC();
                    lcdWriteCtrl(0b00000001);
                    while(demo){
                        temp = getTemp();
                        showTemp(temp);
                        humidity = calHumidity(temp);
                        showHumidity(humidity);
                        if(S4==1){
                            demo=FALSE;
                        }
                    }
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

static void initSysPins(void)
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

static void initADC(void)
{
    ADREF = 0b00000000;
    ADCLK = 0b00000011;
    ADACQ = 0b00000000;
    ADCON0 = 0b10000100;
}

static void initSysDev(void)
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


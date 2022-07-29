#include <xc.h>
#include <limits.h>
#include "gsdf.h"
#include "lcd.h"
#include "humidity.h"
#include "keys.h"
#include "led.h"

#define TRUE 1
#define FALSE 0
#define S4 PORTAbits.RA4
//#define convertRawToCelsius (5*100)/128
#define LCD_RS PORTEbits.RE1 // RS signal for LCD
#define LCD_E PORTEbits.RE0 
#define LCD_DATA PORTD
#define HUMIDITY_LOW_RANGE      (30)
#define HUMIDITY_HIGH_RANGE     (50)


unsigned int result;
unsigned char digitM, digitC, digitX, digit;

static unsigned long timer0_cnt = 0;


static void initSysPins(void);
static void initADC(void);
static void initSysDev(void);


static unsigned long get_time(void)
{
    return timer0_cnt;
}

//void initSysDev2(void);


void __interrupt() isr(void)
{
    if(PIR0bits.TMR0IF == 1)
    {
        PIR0bits.TMR0IF = 0;
        // PORTAbits.RA0 = ~PORTAbits.RA0;
        // PORTAbits.RA1 = ~PORTAbits.RA1;

        // Increment timer count
        if(timer0_cnt >= ULONG_MAX){
            timer0_cnt = 1;
        }
        else{
            timer0_cnt++;
        }
    }
}


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
    initTimer0();
    initPWM6();
    enablePWM6();
	while (loop) 
	{ 
       lcdClearDisplay();
       lcdWriteMessage("Press 1 or 2",1);
       lcdWriteMessage("(1) Temp (2) Keypad" ,2);

    //    while ((key=getKey())==0); // wait for key entry

       // process the user key input for LCD display if given
       switch(getKey())
       	{
            case 0:
                break; // no usesr input
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
       	
        // check humidity
        if(humidity >= HUMIDITY_LOW_RANGE && humidity =< HUMIDITY_HIGH_RANGE){
            //turn on green LED
            onLED(GREEN);
            //turn off yellow LED
            offLED(YELLOW);
            //TODO: irrgation
        }
        else if(humidity < HUMIDITY_LOW_RANGE){
            lcdWriteMessage("Humidity out of range",2);
            // turn on yellow LED
            onLED(YELLOW);
            //turn off green LED
            offLED(GREEN);
            // increase the motor speed
            IncreasePWMDutyCycle();

            //TODO: check timer again ?

            // turn on Buzzer
            BUZZER = 1;
        }
        else {
            lcdWriteMessage("Humidity out of range",2);
            // turn on yellow LED
            onLED(YELLOW);
            //turn off green LED
            offLED(GREEN);
            // reduce the motor speed
            reducePWMDutyCycle();

            //TODO: check timer again ?

            // turn on Buzzer
            BUZZER = 1;
        }
    }
    
}


// void main(void) 
// { 
// 	unsigned char i, key;
//     unsigned int temp;
//     unsigned int humidity;
//     int loop = TRUE;
   
// 	initSysPins();
//     initADC();
//     initSysDev();
//     //initSysDev2();
// 	initLCD(); 
//     initTimer0();
//     initPWM6();
// 	while (loop) 
// 	{ 
//        lcdClearDisplay();
//        lcdWriteMessage("Press 1 or 2",1);
//        lcdWriteMessage("(1) Temp (2) Keypad" ,2);
//        while ((key=getKey())==0); // wait for key entry
//        switch(key)
//        	      {
//            		case '1':
//                     bool demo = TRUE;
//                		initADC();
//                     lcdWriteCtrl(0b00000001);
//                     while(demo){
//                         temp = getTemp();
//                         showTemp(temp);
//                         humidity = calHumidity(temp);
//                         showHumidity(humidity);
//                         if(S4==1){
//                             demo=FALSE;
//                         }
//                         if(humidity >= HUMIDITY_LOW_RANGE && humidity =< HUMIDITY_HIGH_RANGE){
//                             onLED(GREEN);
//                         }
//                         else if(humidity < HUMIDITY_LOW_RANGE){
//                             lcdWriteMessage("Humidity out of range",2);
//                             // turn on yellow LED
//                             onLED(YELLOW);
//                             // increase the motor speed
//                             IncreasePWMDutyCycle();

//                             //TODO: check timer again ?

//                             // turn on Buzzer
//                             BUZZER = 1;
//                         }
//                         else {
//                             lcdWriteMessage("Humidity out of range",2);
//                             // turn on yellow LED
//                             onLED(YELLOW);
//                             // reduce the motor speed
//                             reducePWMDutyCycle();

//                             //TODO: check timer again ?

//                             // turn on Buzzer
//                             BUZZER = 1;
//                         }
//                     }
//                		break;
//            		case '2':
//                		showKeys();
//                		break;
//            	default : 
//                lcdClearDisplay();
//                lcdWriteMessage("Invalid option",2);
//        	}
//        	while ((key=getKey())==0); // wait for key entry
//     	}
// }

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
    // Reset INT External Interrupt Flag bit
    PIR0bits.INTF=0;
    INTPPS=0x01;
    // Interrupt on rising edge of INT pin
    INTCONbits.INTEDG =1;
    // Enables the INT external interrupt
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


/**
 * @brief Initialize timer0
 * @ref The tutorial page for oscillators can be found at:
 * https://microchipdeveloper.com/8bit:osc
 * @ref tutorial for timers:
 * https://exploreembedded.com/wiki/PIC16f877a_Timer
 * 
 */
void initTimer0(void)
{
    // disable all active interrupts
    INTCONbits.GIE = 0;
    // enable the timer0 and set the postscaler to 1:1 
    // set TIM0 to be a 16-bit timer
    T0CON0 = 0b10010000;
    // set the timer0 with synchronize mode and use the system oscillator 
    // (FOSC/4) as the clock source
    // set the prescale rate to 1:4
    T0CON1 = 0b01000010;
    // Set the timer period to 1 second, here the FOSC/4 is interpreted as 8MHz 
    // set high byte
    TMR0H = 0xFE0C;
    // set low byte
    TMR0L = 0x00;
    // reset TMR0 Overflow Interrupt Flag bit
    PIR0bits.TMR0IF = 0;
    // enable the TMR0 Overflow Interrupt 
    PIE0bits.TMR0IE =1;
    // enable all active interrupts
    INTCONbits.GIE =1;
}

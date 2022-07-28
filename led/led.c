#include <xc.h>
#include "config.h"
#include "led.h"

void shiftPortALEDs(void)
{
    int cnt;
    PORTA = 0b00001000;
    for(cnt=0; cnt<3; cnt++)
    {
        __delay_ms(1000);
        PORTA = PORTA >> 1;
    }
}

void togglePortALEDs(void)
{
    unsigned char cnt;
    
    LATA = 0x0F; // ON all LED
    for(cnt = 0; cnt <10; cnt++)
        
    {
        PORTA = ~LATA;
        __delay_ms(500); //delay
        
    }
    PORTA = 0x00; // OFF all LED
       
}

void onLED(led_color_t color)
{
    switch(color)
    {
        case YELLOW:
        {
            PORTAbits.RA2 = 1;
            break;
        }
        case RED:
        {
            PORTAbits.RA0 = 1;
            break;
        }
        case GREEN:
        {
            PORTAbits.RA4 = 1;
            break;
        }
        default:
            break;
    }
}

void offLED(led_color_t color)
{
    switch(color)
    {
        case YELLOW:
        {
            PORTAbits.RA2 = 0;
            break;
        }
        case RED:
        {
            PORTAbits.RA0 = 0;
            break;
        }
        case GREEN:
        {
            PORTAbits.RA4 = 0;
            break;
        }
        default:
            break;
    }
}

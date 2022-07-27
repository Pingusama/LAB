#include "temp.h"
#include "lcd.h"
#include <xc.h>
#include "gsdf.h"

unsigned int getTemp()
{
    unsigned int result;
    ADPCH = 0b00000000;
    __delay_us(5);
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO ==1);
    result = ADRESH*256+ADRESL;
    result = result*3;
    return result;
}

static void tempchange(void)
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


void showTemp(unsigned int temp)
{
    unsigned char key;
    int demo = TRUE;
    char res[20];
    float fres;

    //result = result*convertRawToCelsius;
    digitM=(unsigned char)(temp/1000);
    digitC=(unsigned char)((temp%1000)/100);
    digitX=(unsigned char)((temp%100)/10);
    digit= (unsigned char)(temp%10);
    lcdSetPosition(1,1);
    lcdWriteMessage("Temp read = ",1);
    lcdWriteData(digitM+0x30);
    lcdWriteData(digitC+0x30);
    lcdWriteData(digitX+0x30);
    tempchange();
}


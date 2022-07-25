#include <xc.h>
#include "config.h"


void initSysPins(void);
void initADC(void);
unsigned char readPot(void); //read potentialmeter

void main(void)
{
    unsigned char result;
    
    initSysPins();
    initADC();
    
    while(1)
    {
        result = readPot(); //read the pot value and store in result
        PORTA = result;
        
        
    }
    
}
void initSysPins(void)
{
    ANSELA = 0x00;
    TRISA = 0xF1;
}

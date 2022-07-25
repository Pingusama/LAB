#include <xc.h>
#include "config.h"
void initSysPins(void);
void initADC(void);
unsigned int readPot(void);

void main(void)
{
unsigned int result;
initSysPins();
initADC();

while(1)
{
    result = readPot();
    //PORTA = result;
    if(result >=0 && result <=10)
        PORTA = 0x00;
    else if(result >=11 && result <=100)
        PORTA = 0x02;
    else if(result >=101 && result <=1000)
        PORTA = 0x04;
    else if(result >=1001 && result <1023)
        PORTA = 0x08;
}
}
// Function to configure the ports
void initSysPins(void)
{
ANSELA = 0x00;
TRISA = 0xF1;
}

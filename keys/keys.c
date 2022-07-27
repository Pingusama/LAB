#include "keys.h"
#include <xc.h>
#include "gsdf.h"

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

// TODO: getKey() implementation
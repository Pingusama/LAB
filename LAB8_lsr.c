#include <xc.h>
#include "config.h"
void __interrupt() isr (void){
  if(PIR0bits.INTF == 1)
  {
      PIR0bits.INTF =0;
      PORTAbits.RA1 = ~PORTAbits.RA1;
  }
}

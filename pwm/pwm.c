#include "pwm.h"
#include <xc.h>
#include "gsdf.h"

void initPWM6(void)
{
    // Select Timer2 as base timer for PWM6
    CCPTMRS1 = 0b00000100;
    // Disable PWM6 and set the output to be active high
    PWM6CON = 0b00000000;
    // Set the period with T2 period register
    T2PR = 124;
    // Set the duty cycle high byte to 0x1F
    PWM6DCH = 0b00011111;
    // Set the duty cycle low byte to 0
    PWM6DCL = 0b01000000;
    // Enable timer2 and set 1:128 prescaler and 1:1 postscaler
    T2CON = 0b11110000;
    // Select clock source for Timer2 as Fosc/4
    T2CLKCON = 0b00000001;
    // Route PWM6 waveform to RA2
    RA2PPS = 0x0E;
}


void enablePWM6(void)
{
    PWM6CONbits.EN = 1;
}

void IncreasePWMDutyCycle(void)
{
    //double the duty cycle high byte
    PWM6DCH <= 1;
}

void reducePWMDutyCycle(void)
{
    //cut the duty cycle high byte to half
    PWM6DCH >= 1;
}

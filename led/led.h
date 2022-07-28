
#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <stdio.h>

typedef enum {
    RED=1,
    GREEN=2,
    YELLOW=3
}led_color_t;


void shiftPortALEDs(void);

void togglePortALEDs(void);

void onLED(led_color_t color);

void offLED(led_color_t color);

#endif // __LCD_H__

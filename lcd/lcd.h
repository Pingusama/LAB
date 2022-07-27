
#ifndef __LCD_H__
#define __LCD_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void initLCD();

void lcdWriteCtrl(char x);

void lcdWriteData(char x);

void lcdSetPos(unsigned char row, unsigned char col);

#endif // __LCD_H__

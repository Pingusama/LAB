
#ifndef __LCD_H__
#define __LCD_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void initLCD();

void lcdWriteCtrl(char x);

void lcdWriteData(char x);

void lcdSetPosition(unsigned char r, unsigned char c);

void lcdWriteMessage (char message [],unsigned char row);

void lcdClearDisplay(void);

#endif // __LCD_H__

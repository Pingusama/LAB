
#ifndef __HUMIDITY_H__
#define __HUMIDITY_H__


#include <stdint.h>
#include <stdio.h>

uint8_t get_humidity_from_temp(uint8_t temp);

void display_humidity(uint8_t humd);

#endif // __HUMIDITY_H__

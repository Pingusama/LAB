#include "humidity.h"
#include "lcd.h"
#include <math.h>
#include <string.h>

// to be changed later
#define DEW_POINT       (10U)

#define TEXT_LENGTH     (32)

/**
 * @brief Get the humidity from temp object
 * @ref The formula used is from the following link:
 * https://study.com/learn/lesson/relative-humidity-formula-examples-calculation.html#:~:text=To%20find%20relative%20humidity%20with,%2F%20%7B237.3%20%2B%20dew%20point%7D
 * 
 * @param temp 
 * @description The formula is humidity = 6.11 x 10^{7.5 x dew point} / {237.3 + dew point}
 * @return uint8_t 
 */
uint8_t get_humidity_from_temp(uint8_t temp)
{
    return (uint8_t)((6.11 * pow(10, 7.5 * DEW_POINT)) / (237.3 + DEW_POINT));
}

void display_humidity(uint8_t humd)
{
    char text[TEXT_LENGTH];
    sprintf(text, "%u", humd);

    int i;
    for(i=0;i<strlen(text);i++){
        lcdWriteData(text[i]);
    }
}
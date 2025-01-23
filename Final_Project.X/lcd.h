#ifndef LCD_H
#define LCD_H



#include <xc.h>
#include <string.h>
void init_lcd();
void writeOnLCD(char string[], int size, int row);
void delay_ms(int delay);

#endif
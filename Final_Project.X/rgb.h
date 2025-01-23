#ifndef RGB_
#define RGB_
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define RED_LAT   LATDbits.LATD2
#define GREEN_LAT LATDbits.LATD12
#define BLUE_LAT  LATDbits.LATD3

// ????? ?????? ??????
#define RED_TRIS   TRISDbits.TRISD2
#define GREEN_TRIS TRISDbits.TRISD12
#define BLUE_TRIS  TRISDbits.TRISD3

void initRGB();
void turnOnRGB();
void delay_loop();
#endif
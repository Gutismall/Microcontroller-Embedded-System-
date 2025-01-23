#ifndef CONFIG_H
#define CONFIG_H

#pragma config FNOSC = PRIPLL      // Primary Oscillator with PLL
#pragma config POSCMOD = XT        // Crystal Oscillator Mode
#pragma config FPLLIDIV = DIV_2    // PLL Input Divider
#pragma config FPLLMUL = MUL_20    // PLL Multiplier
#pragma config FPLLODIV = DIV_1    // PLL Output Divider
#pragma config FPBDIV = DIV_2      // Peripheral Clock Divisor
#pragma config FWDTEN = OFF        // Watchdog Timer Disable
#pragma config ICESEL = ICS_PGx1   // ICE/ICD Communication Channel Select
#pragma config JTAGEN = OFF        // Disable JTAG

#define UP 0
#define LEFT 1
#define CENTER 2
#define RIGHT 3
#define DOWN 4

typedef enum {
    HEATING_TOP_AND_BOTTOM,    
    FAN_ASSISTED,              
    GRILL,                      
    FAN_GRILL,                  
    BOTTOM_HEATING,             
    GENTLE_BAKING,                              
    ENOFMODES
} OvenMode;


typedef struct{
    int time;
    int degrees;
    int mode;
}settings;

#endif // CONFIG_H

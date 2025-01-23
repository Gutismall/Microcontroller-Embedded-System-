#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "rgb.h"

#define GetPeripheralClock()    10000000
#define T1_PRESCALE             8
#define TOGGLES_PER_SEC         1
#define T1_TICK          (GetPeripheralClock() / T1_PRESCALE / TOGGLES_PER_SEC)

// ??? ???? ??????
#define SYSCLK 80000000L
#define PBCLK  SYSCLK/2

// ?????? ?????
#define AN0 LATBbits.LATB12
#define AN1 LATBbits.LATB13
#define AN2 LATAbits.LATA9
#define AN3 LATAbits.LATA10
#define CA LATGbits.LATG12
#define CB LATAbits.LATA14
#define CC LATDbits.LATD6
#define CD LATGbits.LATG13
#define CE LATGbits.LATG15
#define CF LATDbits.LATD7
#define CG LATDbits.LATD13
#define DP LATGbits.LATG14
// ??????? ?????? GPIO
void init_gpio() {
    // ????? ?????? ??????? ???????
    TRISGbits.TRISG12 = 0; // CA
    TRISAbits.TRISA14 = 0; // CB
    TRISDbits.TRISD6  = 0; // CC
    TRISGbits.TRISG13 = 0; // CD
    TRISGbits.TRISG15 = 0; // CE
    TRISDbits.TRISD7  = 0; // CF
    TRISDbits.TRISD13 = 0; // CG
    TRISGbits.TRISG14 = 0; // DP

    // ????? ?????? ??????? ???????
    TRISBbits.TRISB12 = 0; // AN0
    TRISBbits.TRISB13 = 0; // AN1
    TRISAbits.TRISA9  = 0; // AN2
    TRISAbits.TRISA10 = 0; // AN3

    // ????? ?? ??????
    LATG = 0x0000;
    LATD = 0x0000;
    LATA = 0x0000;
    LATB = 0x0000;
}

// ??????? ????? ???? ?? ????? ??????
void display_digit(uint8_t digit, uint8_t anode) {
    // ????? ?? ????????
    CA = 1; CB = 1; CC = 1; CD = 1; CE = 1; CF = 1; CG = 1; DP = 1;

    // ????? ???????? ???? ????? ??????
    switch (digit) {
        case 0: CA = 0; CB = 0; CC = 0; CD = 0; CE = 0; CF = 0; CG = 1; break;
        case 1: CA = 1; CB = 0; CC = 0; CD = 1; CE = 1; CF = 1; CG = 1; break;
        case 2: CA = 0; CB = 0; CC = 1; CD = 0; CE = 0; CF = 1; CG = 0; break;
        case 3: CA = 0; CB = 0; CC = 0; CD = 0; CE = 1; CF = 1; CG = 0; break;
        case 4: CA = 1; CB = 0; CC = 0; CD = 1; CE = 1; CF = 0; CG = 0; break;
        case 5: CA = 0; CB = 1; CC = 0; CD = 0; CE = 1; CF = 0; CG = 0; break;
        case 6: CA = 0; CB = 1; CC = 0; CD = 0; CE = 0; CF = 0; CG = 0; break;
        case 7: CA = 0; CB = 0; CC = 0; CD = 1; CE = 1; CF = 1; CG = 1; break;
        case 8: CA = 0; CB = 0; CC = 0; CD = 0; CE = 0; CF = 0; CG = 0; break;
        case 9: CA = 0; CB = 0; CC = 0; CD = 0; CE = 1; CF = 0; CG = 0; break;
        case 10: DP = 0; break;
        default: CA = 1; CB = 1; CC = 1; CD = 1; CE = 1; CF = 1; CG = 1; break;
    }

    // ????? ?? ???????
    AN0 = 1; AN1 = 1; AN2 = 1; AN3 = 1;

    // ????? ?????? ??????
    switch (anode) {
        case 0: AN0 = 0; break;
        case 1: AN1 = 0; break;
        case 2: AN2 = 0; break;
        case 3: AN3 = 0; break;
    }
}
void printOnSevenSeg(const char* num) {
    // ????? GPIO
    init_gpio();
    initRGB();
    //////////////
    // Set instrumentation output pins
    DDPCONbits.JTAGEN = 0;      // Statement is required to use Pin RA0 as IO
    TRISAbits.TRISA0 = 0;       // Set LED0 IO pin for output
    TRISEbits.TRISE0 = 0;       // Use LCD DB0 for timing instrumentation

// Initialize Timer 1 for 1 ms period
    T1CONbits.TCKPS = 0x01;     // Timer 1 pre scale = 8
    T1CONbits.TCS = 0;          // Timer 1 source = PBCLK
    T1CONbits.TGATE = 0;        // Turn gated Timer 1 off
    PR1 = T1_TICK - 1;          // Set T1 period for 1 ms
    T1CONbits.ON = 1;           // Turn Timer 1 on.
    /////////////
    int ms_count = 1000;
    while (ms_count--) {
        RED_LAT = 1; GREEN_LAT = 0; BLUE_LAT = 0;
        if (num[0] != '\0') { 
            display_digit(num[0] - '0', 3); 
        } else {
            display_digit(0, 3); // ????? ?? ??? ?? ??? ????
        }
        for (int i = 0; i < 50; i++);
        RED_LAT = 0; GREEN_LAT = 1; BLUE_LAT = 0;

        // ???? ???? (???? ?????? ???? ???????)
        if (num[1] != '\0') {
            display_digit(num[1] - '0', 2);
        } else {
            display_digit(0, 2);
        }
        for (int i = 0; i < 50; i++);
        RED_LAT = 0; GREEN_LAT = 0; BLUE_LAT = 1;

        // ????? ????????? ?? ????
        display_digit(10, 2); // ????? ?????????? (?? ??)

        // ???? ????? (???? ?????? ?????? ???????)
        if (num[2] != '\0') {
            display_digit(num[2] - '0', 1);
        } else {
            display_digit(0, 1);
        }
        for (int i = 0; i < 50; i++);
        RED_LAT = 1; GREEN_LAT = 1; BLUE_LAT = 0;

        // ???? ????? (???? ?????? ?????? ???????)
        if (num[3] != '\0') {
            display_digit(num[3] - '0', 0);
        } else {
            display_digit(0, 0);
        }
        for (int i = 0; i < 50; i++);
        RED_LAT = 1; GREEN_LAT = 0; BLUE_LAT = 1;

        while(!IFS0bits.T1IF);      // Wait for interrupt flag to be set
        IFS0bits.T1IF = 0;   
    }
}

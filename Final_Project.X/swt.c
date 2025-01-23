#include "swt.h"

void init_swt(){
    TRISFbits.TRISF3 = 1;
    TRISFbits.TRISF5 = 1;
    TRISFbits.TRISF4 = 1;
    TRISDbits.TRISD15 = 1;
    TRISDbits.TRISD14 = 1;
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB9 = 1;
    ANSELBbits.ANSB11 = 0;
    ANSELBbits.ANSB10 = 0;
    ANSELBbits.ANSB9 = 0;
}

int check_swt(int swt){
    if(swt == 0 && PORTFbits.RF3){
        return 0;
    }
    if(swt == 1 && PORTFbits.RF5){
        return 1;
    }
    if(swt == 2 && PORTFbits.RF4){
        return 2;
    }
    if(swt == 3 && PORTDbits.RD15){
        return 3;
    }
    if(swt == 4 && PORTDbits.RD14){
        return 4;
    }
    if(swt == 5 && PORTBbits.RB11){
        return 5;
    }
    if(swt == 6 && PORTBbits.RB10){
        return 6;
    }
    if(swt == 7 && PORTBbits.RB9){
        return 7;
    }
    return 8;
}
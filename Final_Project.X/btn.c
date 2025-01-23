#include "btn.h"

void init_btn(){
    
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
    TRISFbits.TRISF0 = 1;
    TRISBbits.TRISB8 = 1;
    TRISAbits.TRISA15 = 1;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB8 = 0;
}
int check_btn(int btn){
    if (btn == 0 && PORTBbits.RB1 == 1){//up
        Beep();
        return 1;
    }
    if (btn == 1 && PORTBbits.RB0 == 1){//left
        Beep();
        return 1;
    }
    if (btn == 2 && PORTFbits.RF0 == 1){//center
        Beep();
        return 1;
    }
    if (btn == 3 && PORTBbits.RB8 == 1) {//right
        Beep();
        return 1;
    }
    if (btn == 4 && PORTAbits.RA15 == 1) {//down
        Beep();
        return 1;
    }
    return 0;
}
void Beep() {
      for (int i = 0; i < 500; i++) { // ???? ????? ?????? ???
        PORTBbits.RB14 ^= 1; // Toggle ????
        delay_ms(500); // ???? ??? ?? 1kHz (500 ??????????)
    }
}
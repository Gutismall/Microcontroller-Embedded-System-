#include "kpad.h"

void init_kpad(){
    TRISBbits.TRISB14 = 0; // ????? ?? RB14 ??????
    ANSELBbits.ANSB14 = 0;
    PORTBbits.RB14 = 0; // ????? ???? ?-LOW
    TRISA&=0xff00;//led
    TRISCbits.TRISC2=0;//RC2
    TRISCbits.TRISC1=0;//RC1
    TRISCbits.TRISC4=0;//RC4
    TRISGbits.TRISG6=0;//RG6
    ANSELGbits.ANSG6=0;//???????
    TRISCbits.TRISC3 =1;//RC3
    CNPUCbits.CNPUC3;
    TRISGbits.TRISG7=1;//RG7
    ANSELGbits.ANSG7=0;
    CNPUGbits.CNPUG7;
    TRISGbits.TRISG8=1;//RG8
    ANSELGbits.ANSG8=0;//???????
    CNPUGbits.CNPUG8;//?????
    TRISGbits.TRISG9=1;//RG9
    ANSELGbits.ANSG9=0;//???????
    CNPUGbits.CNPUG9;//?????
}

int buttonNumber() {
    if (PORTCbits.RC3 == 0) {
        return 0;
    }
    if (PORTGbits.RG7 == 0) {
        return 1;
    }
    if (PORTGbits.RG8 == 0) {
        return 2;
    }
    if (PORTGbits.RG9 == 0) {
        return 3;
    }
    return -1;
}

int mat(){
    int mat[2] = {0};
    int col;
    PORTCbits.RC2 = 0;
    PORTCbits.RC1 = 1;
    PORTCbits.RC4 = 1;
    PORTGbits.RG6 = 1;
    delay_ms(1000);
    col = buttonNumber();
    if (col != -1) {
        mat[0] = 0;
        mat[1] = col;
        return convert(mat);
    }
    
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 0;
    PORTCbits.RC4 = 1;
    PORTGbits.RG6 = 1;
    delay_ms(1000);
    col = buttonNumber();
    if (col != -1) {
        mat[0] = 1;
        mat[1] = col;
        return convert(mat);
    }
    
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC4 = 0;
    PORTGbits.RG6 = 1;
    delay_ms(1000);
    col = buttonNumber();
    if (col != -1) {
        mat[0] = 2;
        mat[1] = col;
        return convert(mat);
    }
    
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC4 = 1;
    PORTGbits.RG6 = 0;
    delay_ms(1000);
    col = buttonNumber();
    if (col != -1) {
        mat[0] = 3;
        mat[1] = col;
        return convert(mat);
    }
    
    return convert(mat);
}
int convert(int* mat){
    if(mat[0]== 3 && mat[1]== 3){
//        memory[1]^=1;
        return 1;
    }
    if(mat[0]== 2 && mat[1]== 3){
//        memory[2]^=1;
        return 2;
    }
    if(mat[0]== 1 && mat[1]== 3){
//        memory[3]^=1;
        return 3;
    }
    if(mat[0]== 3 && mat[1]== 2){
//        memory[4]^=1;
        return 4;
    }
    if(mat[0]== 2 && mat[1]== 2){
//        memory[5]^=1;
        return 5;
    }
    if(mat[0]== 1 && mat[1]== 2){
//        memory[6]^=1;
        return 6;
    }
    if(mat[0]== 3 && mat[1]== 1)
//        memory[7]^=1;
        return 7;
    if(mat[0]== 2 && mat[1]== 1){
//        memory[8]^=1;
        return 8;
    }
    if(mat[0] == 1 && mat[1] == 1){
//        memory[9]^=1;
        return 9;
    }
    if(mat[0] == 3 && mat[1] == 0){
//        memory[0]^=1;
        return 0;
    }
    
}
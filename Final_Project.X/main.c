#include <sys/attribs.h>
#include <stdio.h>
#include "btn.h"
#include "swt.h"
#include "lcd.h"
#include "config.h"
#include "aic.h"
#include "kpad.h"
#include <math.h>
#include "Seven_Segment.h"
#include "rgb.h"

char string[80];
int timerFlag = 1;
void programSetter();
void degreeSetter();
void timerSetter();
void startProgram();
void initProgramTimer();
void __ISR(_TIMER_4_VECTOR, ipl2) Timer4SR(void);
settings mainSettings;
void intToStr(int min, char *str);

void __ISR(_TIMER_4_VECTOR, ipl2) Timer4SR(void) {    
    if (check_btn(CENTER)) { 
        timerFlag = 0; // Signal to stop the program
    }
    IFS0bits.T4IF = 0; // Clear the Timer 4 interrupt flag
}
void main(){
    
    int mainFlag = 1;

    init_btn();
    init_swt();
    init_lcd();
    ADC_Init();
    init_kpad();
    
    
    
    sprintf(string,"Welcome       ");
    writeOnLCD(string,strlen(string),0);
    sprintf(string,"press BTNC     ");
    writeOnLCD(string,strlen(string),1);
    while(mainFlag){
        if(check_btn(CENTER)){
            clearScreen();
            mainFlag = 0;
        }
    }
    while(1){
        sprintf(string,"T:%2d M:%d D:%3d",mainSettings.time,mainSettings.mode,mainSettings.degrees);
        writeOnLCD(string,strlen(string),0);
        sprintf(string,"Select Mode        ");
        writeOnLCD(string,strlen(string),1);
        if(check_btn(LEFT)){
            degreeSetter();
        }
        if(check_btn(RIGHT)){
            timerSetter();
        }
        if(check_btn(DOWN)){
            programSetter();
        }
        if(check_btn(CENTER)){
            startProgram();
            break;
        }
            
    }
    clearScreen();
    init_gpio();
    sprintf(string,"Done");
    writeOnLCD(string,strlen(string),0);
    while(1);
}

void degreeSetter(){
    int x;
    while(1){
        sprintf(string,"T:%2d M:%d D:%3d",mainSettings.time,mainSettings.mode,mainSettings.degrees);
        writeOnLCD(string,strlen(string),0);
        x = ADC_AnalogRead(2);
        x = x * 240 / 1024;
        sprintf(string,"Degrees : %d    ",x);
        writeOnLCD(string,strlen(string),1);
        if(check_btn(CENTER)){
            mainSettings.degrees = x;
            return;
        }
    }
}
void timerSetter(){
    int timerFlag = 1;
    int time = 0;
    int timeCounter = 0;
    int matt;
    while(timeCounter < 2){
        timeCounter = log10(time)+1;
        sprintf(string,"T:%2d M:%d D:%3d",mainSettings.time,mainSettings.mode,mainSettings.degrees);
        writeOnLCD(string,strlen(string),0);
        matt = mat();
        if(matt == 1){
            time *= 10;
            time += 1;
        }
        if(matt == 2){
            time *= 10;
            time += 2;
        }
//        if(matt == 3){
//            time *= 10;
//            time += 3;
//        }
        if(matt == 4){
            time *= 10;
            time += 4;
        }
        if(matt == 5){
            time *= 10;
            time += 5;
        }
        if(matt == 6){
            time *= 10;
            time += 6;
        }
        if(matt == 7){
            time *= 10;
            time += 7;
        }
        if(matt == 8){
            time *= 10;
            time += 8;
        }
        if(matt == 9){
            time *= 10;
            time += 9;
        }
        if(matt == 0){
            time*= 10;
        }
        sprintf(string,"Timer :%d         ",time);
        writeOnLCD(string,strlen(string),1);
    }
    mainSettings.time = time;
    
}
void programSetter(){
    int programFlag = 1;
    while(programFlag){
        sprintf(string,"T:%2d M:%d D:%3d",mainSettings.time,mainSettings.mode,mainSettings.degrees);
        writeOnLCD(string,strlen(string),0);
        if(check_swt(HEATING_TOP_AND_BOTTOM) == 0){
            sprintf(string,"HEATING T AND B     ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA0 = 1;
            mainSettings.mode = 1;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA0 = 0;
        if(check_swt(FAN_ASSISTED) == 1){
            sprintf(string,"FAN ASSISTED       ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA1 = 1;
            mainSettings.mode = 2;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA1 = 0;
        if(check_swt(GRILL) == 2){
            sprintf(string,"GRILL             ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA2 = 1;
            mainSettings.mode = 3;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA2 = 0;
        if(check_swt(FAN_GRILL) == 3){
            sprintf(string,"FAN GRILL               ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA3 = 1;
            mainSettings.mode = 4;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA3 = 0;
        if(check_swt(BOTTOM_HEATING) == 4){
            sprintf(string,"BOTTOM HEATING                ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA4 = 1;
            mainSettings.mode = 5;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA4 = 0;
        if(check_swt(GENTLE_BAKING) == 5){
            sprintf(string,"GENTLE BAKING                 ");
            writeOnLCD(string,strlen(string),1);
            LATAbits.LATA5 = 1;
            mainSettings.mode = 6;
            if(check_btn(CENTER)){
                programFlag = 0;
            }
            continue;
        }
        else
            LATAbits.LATA5 = 0;
        sprintf(string,"Select Cooking Mode");
        writeOnLCD(string,strlen(string),1);
            
    }
}
void startProgram() {
    initProgramTimer(); // Initialize Timer 4

    int time = mainSettings.time * 100;
    char str[4];

    while (time && timerFlag) { // Run while there is time left and no stop signal
        turnOnRGB(); // Turn on the RGB LEDs

        if (time % 100 == 0) { // Update display every 100 ticks
            time -= 41; // Decrease time (adjust decrement for your timer logic)
        }
//        time--;
//        for(int i = 59;i != 0;i--){
//            if(time<=10)
//                time*=10;
//            time/=100;
//            time*=100;
//            time+=i;
            intToStr(time, str);
            printOnSevenSeg(str);
            
//        }
        // Convert time to string and display it
//        intToStr(time, str);
//        printOnSevenSeg(str);

        time--; // Decrease time on every loop iteration
    }

    T4CONbits.ON = 0; // Disable Timer 4 when the program ends
}

void intToStr(int min, char *str) {
    if(min < 1000){
        if(min < 100){
            if(min < 10){
                sprintf(str, "000%d",min);
                return;
            }
            sprintf(str, "00%d",min);
            return;
        }
        sprintf(str, "0%d",min); // Alternative: Implement manually using loops for learning
        return;
    }
    sprintf(str, "%d",min); // Alternative: Implement manually using loops for learning
}

void initProgramTimer() {
    PR4 = 0xffff;                  // Set the Timer 4 period register (adjust as needed)
    TMR4 = 0;                      // Initialize Timer 4 count to 0

    T4CONbits.TCKPS = 0b111;       // 1:256 prescale value
    T4CONbits.TGATE = 0;           // Disable gated input
    T4CONbits.TCS = 0;             // Use internal clock (PBCLK)
    T4CONbits.ON = 1;              // Turn on Timer 4

    IPC4bits.T4IP = 2;             // Set Timer 4 priority to 2
    IPC4bits.T4IS = 0;             // Set Timer 4 subpriority to 0
    IFS0bits.T4IF = 0;             // Clear Timer 4 interrupt flag
    IEC0bits.T4IE = 1;             // Enable Timer 4 interrupt
    INTCONbits.MVEC = 1;           // Enable multi-vector interrupts
    asm("ei");                     // Enable global interrupts
}
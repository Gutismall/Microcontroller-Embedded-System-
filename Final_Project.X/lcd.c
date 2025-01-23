#include "lcd.h"


void init_lcd() {
    char control[] = {0x38, 0x38, 0x38, 0x0E, 0x06, 0x01};
    TRISBbits.TRISB15 = 0;
    ANSELBbits.ANSB15 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    TRISE &= 0xFF00;
    ANSELEbits.ANSE2 = 0;
    ANSELEbits.ANSE4 = 0;
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    PORTBbits.RB15 = 0;
    PORTDbits.RD5 = 0;
    ANSELEbits.ANSE7 = 0;
    for (int m = 0; m < 6; m++) {
        PORTE = control[m];
        PORTDbits.RD4 = 1;
        PORTDbits.RD4 = 0;
        for (int j = 0; j < 32000; j++);
    }
}

void writeOnLCD(char string[], int size, int row) {
    PORTBbits.RB15 = 0; // Set RS to 0 (command mode)
    PORTDbits.RD5 = 0;  // Set RW to 0 (write mode)
    
    // Set cursor position based on row
    if (row == 0) {
        PORTE = 0x80;  // Move cursor to the beginning of the first row
    } else if (row == 1) {
        PORTE = 0xC0;  // Move cursor to the beginning of the second row
    }
    
    PORTDbits.RD4 = 1;  // Enable = 1
    delay_ms(1000);        // Short delay
    PORTDbits.RD4 = 0;  // Enable = 0
    
    PORTBbits.RB15 = 1; // Set RS to 1 (data mode)
    for (int i = 0; i < size; i++) {
        PORTE = string[i];  // Send character to LCD
        PORTDbits.RD4 = 1;  // Enable = 1
        delay_ms(10000);        // Short delay for LCD to process
        PORTDbits.RD4 = 0;  // Enable = 0
    }
}

void delay_ms(int delay) {
    for(int i = 0;i < delay;i++){
        
    }
}

void clearScreen(){
    LATBbits.LATB15 = 0;
    delay_ms(10000);  
	// Configure IO Port data pins as output.
    TRISE &= 0xFF;
    delay_ms(10000);  
	// clear RW
    LATDbits.LATD5 = 0;

    // access data as contiguous 8 bits, using pointer to the LSB byte of LATE register
    unsigned char *pLCDData = (unsigned char *)(0xBF886430);
    *pLCDData = 0x01;

    delay_ms(10000);    

	// Set En
    LATDbits.LATD4 = 1;

    delay_ms(10000);  
	// Clear En
    LATDbits.LATD4 = 0;

    delay_ms(10000);
	// Set RW
    LATDbits.LATD5 = 1;
}
//void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char idxPos)
//{
//	// crop string to 0x27 chars
//	int len = strlen(szLn);
//	if(len > 0x27)
//	{
//        szLn[0x27] = 0; // trim the string so it contains 40 characters 
//		len = 0x27;
//	}
//
//	// Set write position
//	unsigned char bAddrOffset = (idxLine == 0 ? 0: 0x40) + idxPos;
//	LCD_SetWriteDdramPosition(bAddrOffset);
//
//	unsigned char bIdx = 0;
//	while(bIdx < len)
//	{
//		LCD_WriteDataByte(szLn[bIdx]);
//		bIdx++;
//	}
//}
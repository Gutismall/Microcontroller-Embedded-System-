# Embedded System Project for PIC32 Microcontroller

## Project Overview
This project implements an embedded system designed for the **PIC32 microcontroller**, leveraging its ability to interact with multiple peripherals. The system provides user interaction through buttons, switches, an LCD screen, a seven-segment display, and an RGB LED module. The application demonstrates advanced embedded programming concepts, real-time processing, and hardware-software integration.

## Microcontroller
The system is built for the **PIC32 microcontroller**, a 32-bit MCU well-suited for real-time embedded systems. It is programmed using the **C language** within the MPLAB X IDE. The PIC32's performance and peripheral capabilities make it ideal for applications requiring precise control and responsiveness.

## Project Files and Their Purposes

- **main.c**: Acts as the entry point for the program, initializing peripherals and handling the main application logic.
- **btn.c / btn.h**: Manages the initialization and state reading of push buttons, including debouncing and event handling.
- **swt.c / swt.h**: Handles the configuration and reading of switches to detect user input.
- **lcd.c / lcd.h**: Implements functions to control the LCD display, including writing text and clearing the screen.
- **kpad.c / kpad.h**: Manages keypad input, providing functions to initialize and read user input.
- **Seven_Segment.c / Seven_Segment.h**: Controls the seven-segment display, including initialization and displaying numbers or characters.
- **rgb.c / rgb.h**: Handles the RGB LED module, allowing control of red, green, and blue components.
- **aic.c / aic.h**: Manages analog input and conversion, such as ADC readings from sensors.
- **audio.c / audio.h**: Provides functionality for audio output, like generating tones or sounds.
- **config.h**: Contains configuration settings for the PIC32 microcontroller, including clock and peripheral initialization.


## How to Run
1. Open the project in MPLAB X IDE using MPLAB XC32 C-Compiler 4.45v.
2. Build the project using the appropriate toolchain.
3. Flash the program to the PIC32 microcontroller using a compatible programmer/debugger.
4. Interact with the system using the peripherals (buttons, switches, LCD, keypad, etc.).

## Demo Video


https://github.com/user-attachments/assets/780fd8df-2b61-4fea-ae7c-f94938050872


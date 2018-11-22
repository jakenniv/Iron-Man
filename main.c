/*
 * File:        main.c
 * Author:      nathanaelrolander
 * Created:     Nov 16, 2018, 5:23 PM
 *
 * Description: Main code for Iron Man project rover
 */

#include <delays.h>
#include <p18cxxx.h>

#pragma config FOSC = INTIO67, PLLCFG = OFF, PRICLKEN = ON, FCMEN = ON, \
               PWRTEN = OFF
#pragma config BOREN = SBORDIS, BORV = 250, WDTEN = OFF, WDTPS = 4096, \
               PBADEN = OFF
#pragma config HFOFST = OFF, MCLRE = EXTMCLR, STVREN = ON, LVP = OFF, DEBUG = ON

#define SERVO_STOP 0x17
#define SERVO_GO_R 0x24
#define SERVO_BACK_R 0x09
#define MAX_SUPPORTED_MODE 4

// Rover motion state
typedef enum { STOP, FORWARD, BACK, RIGHT, LEFT } MotionState;

unsigned char device, command, value, i, done;
unsigned int result, temp;
unsigned char buffer[16];
MotionState mode = STOP;

/** Delay for 18 * Tcy */
void DelayFor18TCY(void) {
    for (i = 0; i < 12; i++) { Nop(); }
}

/**
 * Delay for 15ms
 * Cycles = (TimeDelay * Fosc) / 4
 * Cycles = (15ms * 16MHz) / 4
 * Cycles = 60,000
 */
void DelayPORXLCD(void) { Delay1KTCYx(60); }

/**
 * Delay for 5ms
 * Cycles = (TimeDelay * Fosc) / 4
 * Cycles = (5ms * 16MHz) / 4
 * Cycles = 20,000
 */
void DelayXLCD(void) { Delay1KTCYx(20); }

/** Handles updating the servo's rotation based on the current mode */
void updateServos(void) {
    // Update based on what mode the rover is currently in
    switch (mode) {
        case STOP:
            CCPR2L = SERVO_STOP;
            CCPR3L = SERVO_STOP;
            break;
        case FORWARD:
            CCPR2L = SERVO_GO_R;
            CCPR3L = SERVO_BACK_R;
            break;
        case BACK:
            CCPR2L = SERVO_BACK_R;
            CCPR3L = SERVO_GO_R;
            break;
        case LEFT:
            CCPR2L = SERVO_BACK_R;
            CCPR3L = SERVO_BACK_R;
            break;
        case RIGHT:
            CCPR2L = SERVO_GO_R;
            CCPR3L = SERVO_GO_R;
            break;
    }
}

void main(void) {
    // Configure the Oscillator for 1 MHz internal oscillator operation
    OSCCON2 = 0x00;  // No 4X PLL
    OSCCON = 0x30;   // 1MHZ

    // Port A configuration
    TRISA = 0xFF;   // Input
    ANSELA = 0x00;  // Digital

    // Port D configuration
    TRISD = 0x00;   // Output
    ANSELD = 0x00;  // Digital

    // Port B configuration
    TRISB = 0x00;   // Output
    ANSELB = 0x00;  // Digital

    // Port C configuration
    TRISC = 0x00;   // Output
    ANSELC = 0x00;  // Digital

    // CCPxCON config
    CCP2CON = 0x1C;
    CCP3CON = 0x1C;

    // Set Timer 2 for CCP2CON and CCP3CON
    CCPTMRS0 = 0x00;

    // T2CON config
    T2CON = 0x06;

    // Configure interrupt - high-priority "interrupt-on-change" for port B,
    // pin 4 (RB4)
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 0;
    INTCONbits.RBIE = 1;
    INTCON2bits.RBIP = 1;
    IOCB = 0x10;

    // Set up the Timer 0 for 8 bit operation with Input from internal
    // clock divided by 4
    T0CON = 0xD1;

    // Start with both servos at STOP initially
    mode = STOP;
    CCPR2L = SERVO_STOP;
    CCPR3L = SERVO_STOP;

    while (1) {
        // Check if the full code has been read yet
        if (done == 1) {
            // Clear result
            result = 0;

            for (i = 0; i < 12; i++) {
                // Shift the previous bits one to the right since LSB is sent
                // first
                result = result >> 1;

                // If it is a 1, shift in a 1 into the 12th bit
                if (buffer[i] > 70) result |= 0x0800;
            }

            // Device is upper 5 bits
            device = result >> 7;
            // Mask off lower 7 bits to determine command
            command = (result & 0x7f);

            // Update the command each time, if it's a valid command
            if (command < MAX_SUPPORTED_MODE && command > 0) {
                mode = command;
                updateServos();
            }

            // Delay before checking again
            Delay10KTCYx(5);
        }
    }
}

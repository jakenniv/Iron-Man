/* 
 * File:   main.c
 * Author: nathanaelrolander
 *
 * Created on November 16, 2018, 5:23 PM
 */

#include <p18cxxx.h>
#include <delays.h>

#pragma config FOSC=INTIO67, PLLCFG=OFF, PRICLKEN=ON,FCMEN=ON, PWRTEN=OFF
#pragma config BOREN=SBORDIS, BORV=250, WDTEN=OFF, WDTPS=4096, PBADEN=OFF
#pragma config HFOFST=OFF, MCLRE=EXTMCLR, STVREN=ON, LVP=OFF, DEBUG= ON

unsigned char device, command, value, i, done;
unsigned int result, temp;
unsigned char buffer[16];
unsigned char mode = 0;

void low_ISR(void);
void high_ISR(void);

#pragma code high_vector = 0x08	// force the following statement to start at
void high_interrupt(void) { 	// 0x08
    _asm 
    goto  high_ISR
    _endasm 
}

#pragma code 			// Return to the default code section
#pragma interrupt high_ISR 
void high_ISR(void) {
    // Handle high-priority interrupts
    if (PORTBbits.RB4 == 0) {
        // Handle falling edge
        // Reset the timer to start it
        TMR0L = 0x00;
    } else {
        // Handle rising edge
        // Read the timer value, since the timer was started on the falling edge
        value = TMR0L;
        
        if (value > 140) {
            // Start bit, reset value counter and whatnot
            i = 0;
            done = 0;
        } else {
            buffer[i] = value;
            i++;
        }
    }
    
    // If the first 11 bits have been handled then reset
    if (i > 11) {
        done = 1;
        i = 0;
    }
    
    // Allow next edge to be handled
    INTCONbits.RBIF = 0;
}

void DelayFor18TCY(void) {
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}

void DelayPORXLCD(void) {
    Delay1KTCYx(60); // Delay of 15ms
    // Cycles = (TimeDelay * Fosc) / 4
    // Cycles = (15ms * 16MHz) / 4
    // Cycles = 60,000
    return;
}

void DelayXLCD(void) {
    Delay1KTCYx(20); // Delay of 5ms
    // Cycles = (TimeDelay * Fosc) / 4
    // Cycles = (5ms * 16MHz) / 4
    // Cycles = 20,000
    return;
}

void main(void) {
    // Configure the Oscillator for 1 MHz internal oscillator operation
	OSCCON2 = 0x00; // No 4X PLL
	OSCCON = 0x30;  // 1MHZ
    
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
    
    //CCPxCON config 
    CCP2CON = 0x1C;
    CCP3CON = 0x1C; 
    
    //Set Timer 2 for CCP2CON and CCP3CON
    CCPTMRS0 = 0x00;
    
    //T2CON config
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
    
    //Set CCPR2L 
    CCPR2L = 0x19; //STOP
    CCPR3L = 0x19; //STOP
    
    while (1) {
        PORTD = 0x00;
        
        CCPR2L = 0x09; //REVERSE
        Delay10KTCYx(100);
        CCPR2L = 0x24;  //FORWARD
        Delay10KTCYx(100);
        CCPR2L = 0x17; //STOP
        Delay10KTCYx(100);        
        // Check if the full code has been read yet
        if (done == 1) {
            // Clear result
            result = 0;
        
            for (i = 0; i < 12; i++) {
                // Shift the previous bits one to the right since LSB is sent first
                result = result >> 1;

                // If it is a 1, shift in a 1 into the 12th bit
                if (buffer[i] > 70) result |= 0x0800;
            }
            
            // Device is upper 5 bits
            device = result >> 7;
            // Mask off lower 7 bits to determine command
            command = (result & 0x7f);
            
            // Resolve what command was sent by glove
            switch (command) {
                case 0: // STOP
                    break;
                case 1: // FORWARD
                    break;
                case 2: // BACK
                    break;
                case 3: // LEFT
                    break;
                case 4: // RIGHT
                    break;
            }
            
            // Delay before checking again
            Delay10KTCYx(5); 
        }
    }
}

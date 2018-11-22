#pragma code high_vector = 0x08  // force the following statement to start at
void high_interrupt(void) {      // 0x08
    _asm goto high_ISR _endasm
}

#pragma code  // Return to the default code section
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
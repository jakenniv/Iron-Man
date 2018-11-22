/** Delay for 18 * Tcy */
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
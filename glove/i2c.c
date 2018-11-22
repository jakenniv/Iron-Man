// Various helper functions for working with I2C

void I2C_writeByte(unsigned char deviceAddr, unsigned char regAddr,
                   unsigned char data) {
    SSP2CON2bits.SEN = 1;
    while (SSP2CON2bits.SEN) {};
    SSP2BUF = deviceAddr + 0;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2BUF = regAddr;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2BUF = data;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2CON2bits.PEN = 1;
    while (SSP2CON2bits.PEN) {};
}

unsigned char I2C_readByte(unsigned char deviceAddr, unsigned char regAddr) {
    SSP2CON2bits.SEN = 1;
    while (SSP2CON2bits.SEN) {};
    SSP2BUF = deviceAddr + 0;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2BUF = regAddr;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2CON2bits.RSEN = 1;
    while (SSP2CON2bits.RSEN) {};
    SSP2BUF = deviceAddr + 0x01;
    while (SSP2STATbits.R_NOT_W) {};
    SSP2CON2bits.RCEN = 1;
    while (SSP2CON2bits.RCEN) {};
    SSP2CON2bits.PEN = 1;
    while (SSP2CON2bits.PEN) {};

    return SSP2BUF;
}
/*
 * File:        main.c
 * Author:      nathanaelrolander
 * Created:     Nov 22, 2018, 12:38 AM (woo midnight coding on Thanskgiving!)
 *
 * Description: Main code for Iron Man project glove
 */

#include <delays.h>
#include <p18cxxx.h>
#include "delays.h"
#include "i2c.h"
#include "mpu6050.h"

#pragma config FOSC = INTIO67, PLLCFG = OFF, PRICLKEN = ON, FCMEN = ON, \
               PWRTEN = OFF
#pragma config BOREN = SBORDIS, BORV = 250, WDTEN = OFF, WDTPS = 4096, \
               PBADEN = OFF
#pragma config HFOFST = OFF, MCLRE = EXTMCLR, STVREN = ON, LVP = OFF, DEBUG = ON

void main(void) {}
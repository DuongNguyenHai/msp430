/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include <msp430g2553.h>
#include "UART.h"

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    char *str = "hello";

    // make the LED pin an output for P1.0
    P1DIR |= 0x01;

    UART_Init(9600);

    while (1)
    {
        __delay_cycles(1000000);
        // toggle the LED
        // P1OUT ^= 0x01;
        UART_Write_String(str);
         __delay_cycles(1000000);
    }

    return 0;
}

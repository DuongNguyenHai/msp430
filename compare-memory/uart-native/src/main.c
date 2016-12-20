/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include <msp430g2553.h>
#include <uart.h>

int main(void)
{
   WDTCTL = WDTPW + WDTHOLD;
   uart_init(9600);

   while (1)
   {
      __delay_cycles(1000000);
      uart_println("hello");
   }

   return 0;
}

// Programming...
// Writing  370 bytes at c000...
// Writing   32 bytes at ffe0...
// Done, 402 bytes total

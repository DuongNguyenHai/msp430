#include <msp430g2553.h>
#include "uart.h"

Uart uart(9600);

int  main() {

  WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

   while (1) {
      uart.println("hello world");  // print with fixed size
      // uart.println_long(123456);
      uart.println_double(123.456);

   }

   return 0;
}

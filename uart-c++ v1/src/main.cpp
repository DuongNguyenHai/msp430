#include "msp430g2553.h"
#include "uart.h"

Uart uart(9600);

int  main() {

  WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

   while (1) {
      uart.println("hello");
      uart.println(123456);
      uart.println(123);
   }

   return 0;
}

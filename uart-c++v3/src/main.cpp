#include "msp430g2553.h"
#include "uart.h"

Uart uart(9600);

int  main() {

  WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

   while (1) {
      uart.println("hello");  // print with fixed size

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));

      uart.println(num(123));
      uart.println(num(456));
      uart.println(num(123));
      uart.println(num(456));


      uart.println(num(123456));

   }

   return 0;
}

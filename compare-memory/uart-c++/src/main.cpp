#include <msp430g2553.h>
#include <uart.h>

int main() {
   WDTCTL = WDTPW + WDTHOLD;
   Uart Serial(9600);
   while(1) {
      __delay_cycles(1000000);
      Serial.println("hello");
   }

   return 0;
}

// Programming...
// Writing  396 bytes at c000...
// Writing   32 bytes at ffe0...
// Done, 428 bytes total

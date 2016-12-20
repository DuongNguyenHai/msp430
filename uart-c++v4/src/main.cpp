#include "msp430g2553.h"
#include "uart.h"

Uart uart(9600);

int  main() {

   WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog
   _data_float dt;
   // dt.num = (double)1.23;
   dt.b[0] = 0b10100100;
   dt.b[1] = 0b01110000;
   dt.b[2] = 0b10011101;
   dt.b[3] = 0b00111111;
   dt.b[4] = 0;
   dt.b[5] = 0;
   dt.b[6] = 0;
   dt.b[7] = 0;
   double k;
   while (1) {

      while(uart.available()) {
         int n = uart.readNumber(k);
         uart.print("bytes: ");
         uart.println(n);
         uart.print("number: ");
         uart.println(k);
         // return 0;
      }

      // uart.print("b0:"); uart.println(dt.b[0], BIN);
      // uart.print("b1:"); uart.println(dt.b[1], BIN);
      // uart.print("b2:"); uart.println(dt.b[2], BIN);
      // uart.print("b3:"); uart.println(dt.b[3], BIN);
      // uart.print("b4:"); uart.println(dt.b[4], BIN);
      // uart.print("b5:"); uart.println(dt.b[5], BIN);
      // uart.print("b6:"); uart.println(dt.b[6], BIN);
      // uart.print("b7:"); uart.println(dt.b[7], BIN);
      // uart.print("dt.num:"); uart.println(dt.num);
      uart.writeNumber((float)1.23);
      __delay_cycles(1000000);
      __delay_cycles(1000000);
      __delay_cycles(1000000);
      __delay_cycles(1000000);
      //
      // uart.println("Sending: ");
      // uart.writeNumber((long)10);
      // __delay_cycles(1000000);
      // __delay_cycles(1000000);
      // __delay_cycles(1000000);
      // __delay_cycles(1000000);
      return 0;
   }

   return 0;
}

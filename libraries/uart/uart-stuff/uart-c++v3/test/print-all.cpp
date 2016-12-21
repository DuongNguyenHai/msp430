#include "msp430g2553.h"
#include "uart.h"

Uart uart(9600);

int  main() {

  WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

   while (1) {
      uart.print("hello World", 5);  // print with fixed size
      uart.print(';');
      __delay_cycles(1000000);
      uart.println("Test print data: char/unsigned char/int/unsigned int/long/unsigned long/float/double as ASCII text");
      uart.print(';');                 // use ';' as terminator character to readStringUntil(). when wanna test with another MCU (arduino)
      uart.println(num(127));               // print max of signed char
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num(-128));              // print min of signed char
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num(255));               // print max of unsigned char
      uart.print(';');
      __delay_cycles(1000000);

      uart.println(num(32767));             // print max of signed int
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num(-32768));             // print min of signed int
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num(65535));             // print max of unsigned int
      uart.print(';');
      __delay_cycles(1000000);

      uart.println(num(-2147483647));       // print min of signed log
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num(2147483647));         // print max of signed long
      uart.print(';');
      __delay_cycles(1000000);
      uart.println((unsigned long)(4294967295));        // print max of unsigned long
      uart.print(';');
      __delay_cycles(1000000);

      uart.println(num_float(1.23));              // print float/double
      uart.print(';');
      __delay_cycles(1000000);
      uart.println(num_float(-1.23));             // print float/double
      uart.print(';');
      __delay_cycles(1000000);

   }

   return 0;
}

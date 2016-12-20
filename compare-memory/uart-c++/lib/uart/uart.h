#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>

class Uart {

public :
   Uart(unsigned long BAUDRATE);
   int print(const char *str);
   int print(unsigned char str);
   int println(const char *str);
   char getchar();

private:
   unsigned long BAUDRATE;

};

#endif

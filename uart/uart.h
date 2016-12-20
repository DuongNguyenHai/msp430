#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>

#define CALDCO_UART  *(char *)0x10BE
#define CALBC1_UART  *(char *)0x10BF

extern unsigned long BAUDRATE;

int uart_init(unsigned long BAUDRATE);
int uart_putchar(unsigned char c);
int uart_print(const char *str);
int uart_println(const char *str);

#endif

#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <msp430g2553.h>

extern unsigned long BAUDRATE;

int uart_init(unsigned long BAUDRATE);
int uart_putchar(unsigned char c);
int uart_print(const char *str);
int uart_println(const char *str);

#ifdef __cplusplus
}
#endif

#endif

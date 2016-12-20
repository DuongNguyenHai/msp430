#include "uart.h"

unsigned long BAUDRATE;
unsigned long SMCLK_F=1000000;

int uart_init(unsigned long BAUDRATE) {

	WDTCTL = WDTPW + WDTHOLD;                 	// Stop WDT
	UCA0CTL0 = 0;								// 8 bit, no parity, LSB, 1 stop bit, Asynchronous
	UCA0CTL1 |= UCSSEL_2; 					// Set clock source to SMCLK

	P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD

	unsigned int factor = SMCLK_F/BAUDRATE;
   UCA0BR0 = (unsigned char) factor&0x00FF;
   factor >>= 8;
   UCA0BR1 = (unsigned char) (factor&0x00FF);

	UCA0MCTL = UCBRS_5;                        // Modulation UCBRSx = 5
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

	__bis_SR_register(GIE);                  // interrupts enabled

	return 0;
}

int uart_putchar(unsigned char c) {
	while (!(IFG2&UCA0TXIFG));                  // USCI_A0 TX buffer ready?
	UCA0TXBUF = c;                    		     // TX -> RXed character
	return 0;
}

int uart_print(const char *str) {
   int state = -1;
   if (str != 0) {
      state = 0;
      while ( *str != '\0' ) {
         while (!(IFG2 & UCA0TXIFG));
         UCA0TXBUF = *str; 
         if (*str == '\n') {
            while (!(IFG2 & UCA0TXIFG));
            UCA0TXBUF = '\r';
         }
         str++;
      }
   }
   return state;
}

// transmit string without the last '\0'.
int uart_println(const char *str) {
   uart_print(str);
   uart_putchar('\r');
   uart_putchar('\n');
   return 0;
}

char uart_getchar() {
   while (!(IFG2&UCA0RXIFG));                   // wait unitl receive character
   return UCA0RXBUF;
}
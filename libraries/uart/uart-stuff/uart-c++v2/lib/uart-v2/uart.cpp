#include "uart.h"

struct baud_config {
	unsigned long baud_val;
	unsigned int UCAxBR0_val;
	unsigned int UCAxBR1_val;
	unsigned int UCAxMCTL_val;
};

struct RX_buff {
	char c[BUFF_SIZE];
	unsigned char head;
	unsigned char tail;
};

// Look at table in MSP430x2xx Family User’s Guide
static const struct baud_config baud_tb[] = {
	{9600, 104, 0, UCBRS_1},
	{115200, 8, 0, UCBRS2 + UCBRS0}
};

static struct RX_buff rx_buff = { {0}, 0, 0};

Uart::Uart(unsigned long BAUDRATE) {

	WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
	UCA0CTL0 = 0;					// 8 bit, no parity, LSB, 1 stop bit, Asynchronous

	if (CALBC1_1MHZ==0xFF) {  // If calibration constant erased
		while(1);          	// do not load, trap CPU!!
	}

   DCOCTL  = 0;             // Select lowest DCOx and MODx settings
   BCSCTL1 = CALBC1_1MHZ;   // Set range
   DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation

	P1SEL = BIT1 + BIT2 ;     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;    // P1.1 = RXD, P1.2=TXD

	UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK, USCI_A0 disabled

	for(int i=0; i< sizeof(baud_tb)/sizeof(baud_tb[0]); i++) {
		if(BAUDRATE==baud_tb[i].baud_val) {
			UCA0BR0   =  baud_tb[i].UCAxBR0_val;	// set register UCAxBR0
			UCA0BR1   =  baud_tb[i].UCAxBR1_val;	// set register UCAxBR1
			UCA0MCTL  =  baud_tb[i].UCAxMCTL_val;  // Set modulation
			break;
		}
	}

	UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0
	// IE2 |= UCA0TXIE;               // Enable the Transmit interrupt
   IE2 |= UCA0RXIE;               // Enable the Receive  interrupt
   __bis_SR_register(GIE);                     // Enable the global interrupt
}

size_t Uart::write(char c) {
	while (!(IFG2 & UCA0TXIFG));                  // USCI_A0 TX buffer ready?
	UCA0TXBUF = c;                    		     // TX -> RXed character
	return 1;
}

size_t Uart::write(const char *s, size_t size) {
	size_t n = 0;
	while (size--) {
		n += write(*s++);
	}
	return n;
}

size_t Uart::print(char c) {
	return write(c);
}

size_t Uart::print(const char *s) {
	return write((const char *)s, strlen(s));
}

size_t Uart::print_size(const char *s, size_t size) {
	return write((const char *)s, size);
}

size_t Uart::print_unsigned_char(unsigned char num, int base) {
	return print_unsigned_long((unsigned long) num, base);
}

size_t Uart::print_int(int num, int base) {
  return print_unsigned_long((long) num, base);
}

size_t Uart::print_unsigned_int(unsigned int num, int base) {
  return print_unsigned_long((unsigned long) num, base);
}

size_t Uart::print_long(long num, int base) {
	if (base == 0) {
		return write(num);
	} else if (base == 10) {
		if (num < 0) {
			unsigned char t = print('-');
			num = -num;
			return printNumber(num, 10) + t;
		}
		return printNumber(num, 10);
	} else {
		return printNumber(num, base);
	}
}

size_t Uart::print_unsigned_long(unsigned long num, int base) {
	if (base == 0) return write(num);
	else return printNumber(num, base);
}

size_t Uart::print_double(double num, int digits) {
	return printFloat(num, digits);
}

size_t Uart::println(void) {
  size_t n = print('\r');
  n += print('\n');
  return n;
}

size_t Uart::println(char c) {
	size_t n = print(c);
	n += print('\n');
   return n;
}

size_t Uart::println(const char *s) {
   size_t n = print(s);
	n +=  println();
	return n;
}

size_t Uart::println_size(const char *s, size_t size) {
   size_t n = print_size(s, size);
	n +=  println();
	return n;
}

size_t Uart::println_unsigned_char(unsigned char num, int base) {
	size_t n = print_unsigned_char(num, base);
	n +=  println();
	return n;
}

size_t Uart::println_int(int num, int base) {
	size_t n = print_int(num, base);
	n +=  println();
	return n;
}

size_t Uart::println_unsigned_int(unsigned int num, int base) {
	size_t n = print_int(num, base);
	n +=  println();
	return n;
}

size_t Uart::println_long(long num, int base) {
	size_t n = print_long(num, base);
	n +=  println();
	return n;
}

size_t Uart::println_unsigned_long(unsigned long num, int base) {
	size_t n = print_unsigned_long(num, base);
	n +=  println();
	return n;
}

size_t Uart::println_double(double num, int digits) {
	size_t n = print_double(num, digits);
	n +=  println();
	return n;
}

size_t Uart::printNumber(unsigned long n, int base) {
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	if (base < 2) base = 10;

	do {
		unsigned long m = n;
		n /= base;
		char c = m - base * n;
		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	return print(str);
}

size_t Uart::printFloat(double number, unsigned char digits) {

	size_t n = 0;
	// Handle negative numbers
	if (number < 0.0) {
		n += print('-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
		rounding /= 10.0;

	number += rounding;

	// Extract the integer part of the number and print it
	long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	n += print(int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0) {
		n += print(".");
	}

	// Extract digits from the remainder one at a time
	while (digits-- > 0) {
		remainder *= 10.0;
		int toPrint = int(remainder);
		n += print(toPrint);
		remainder -= toPrint;
	}

	return n;
}

size_t Uart::writeNum(float num, unsigned char type) {
	_data dt = {0, num};
	size_t n = 0;
	for (char i = 0; i < type; i++) {
		n +=print(dt.b[i]);
	}
	return n;
}

size_t Uart::printSpecial(const char *s, char del) {
	size_t n = print(s);
	n += print(del);
	return n;
}

size_t Uart::printSpecial(const char *s, const char *s2) {
	size_t n = print(s);
	n += print(s2);
	return n;
}

size_t Uart::printString(const char *s) {
	return printSpecial(s);
}

size_t Uart::write_unsigned_char(unsigned char num) {
	return writeNum((float)num, 1);
}

size_t Uart::write_int(int num) {
	writeNum((float)num, 2);
}
//
size_t Uart::write_unsigned_int(unsigned int num) {
	writeNum((float)num, 2);
}

size_t Uart::write_long(long num) {
	writeNum((float)num, 4);
}

size_t Uart::write_unsigned_long(unsigned long num) {
	writeNum((float)num, 4);
}

size_t Uart::write_float(float num) {
	writeNum((float)num, 4);
}

size_t Uart::available() {
	return (unsigned char )(BUFF_SIZE + rx_buff.head - rx_buff.tail) % BUFF_SIZE;
}

char Uart::read() {

	if(rx_buff.tail==rx_buff.head) {
		return -1;
	}
	char c = rx_buff.c[rx_buff.tail];
	rx_buff.tail = (unsigned char)(rx_buff.tail+1) % (unsigned char)BUFF_SIZE;
	return c;
}

char Uart::peek() {

	if(rx_buff.tail==rx_buff.head)
		return -1;

	return rx_buff.c[rx_buff.tail];
}

char Uart::readTimeOut() {
	for (size_t i = 0; i < 10; i++) {
		char c = read();
		if(c!=-1)
			return c;
		__delay_cycles(10000);
	}
	return -1;
}

size_t Uart::readString(char *s) {
	char *p = s;
	while(1) {
		char c = readTimeOut();
		if(c==-1 || c=='\0') break;
		*s++ = c;
	}
	*s = '\0';
	return s-p;
}

size_t Uart::readString(char *s, unsigned char pos) {
	return readStringFromIndexTo(s, 0, pos);
}

size_t Uart::readStringUntil(char *s, char del) {
	char *p = s;
	while(1) {
		char c = readTimeOut();
		if(c==-1) {						// not found any more character
			memset(p, '\0', 1);
			return -1;
		}
		if(c==del) break;				// break when delimiter has detected
		*s++ = c;
	}
	*s = '\0';
	return s-p;
}

size_t Uart::readStringFromTo(char *s, const unsigned char tail, const unsigned char head) {
	char *p = s;
	bool tail_flag = false;
	while(1) {
		char c = readTimeOut();
		if(c==-1)						// not found any more character
			break;
		if(tail_flag) {
			if(c==head) break;
			*s++ = c;
		}
		if(c==tail)
			tail_flag = true;
	}
	*s = '\0';
	return s-p;
}

size_t Uart::readStringFromIndexTo(char *s, unsigned char index, unsigned char pos) {
	char *p = s;
	unsigned char n = 0;
	while(1) {
		char c = readTimeOut();
		if(c==-1)	// not found any more character
			break;

		n++;
		if(n>pos+1) break;
		if( index<n && n<=pos+1 )
			*s++ = c;
	}
	*s = '\0';
	return s-p;
}

//////////////////////////////////////////
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {

	while (!(IFG2 & UCA0RXIFG));                   // wait unitl receive character
	if( ((BUFF_SIZE + rx_buff.head - rx_buff.tail) % BUFF_SIZE) < (BUFF_SIZE-1) ) {
		rx_buff.c[rx_buff.head] = UCA0RXBUF;
		rx_buff.head = (rx_buff.head + 1) % BUFF_SIZE;
	}

	IFG2 &= ~UCA0RXIFG; // Clear RX flag
}

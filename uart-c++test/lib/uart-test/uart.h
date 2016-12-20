#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>
#include <string.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#define UN_CHAR 1
#define INT 2
#define UN_INT 2
#define LONG 4
#define UN_LONG 4
#define DOUBLE 8

#define BUFF_SIZE 33 // will getting error if BUFF_SIZE > 100 (currently test is 199)

union _data {
   char b[8];
   double num;
};

class Uart {

public :
   Uart(unsigned long BAUDRATE=9600);
   size_t write(char c);
   size_t write(const char *s, size_t size);

   // Print data to the serial port as human-readable ASCII text
   size_t print(char c);                                 // send a character
   size_t print(const char *s, size_t size = -1);        // send a string with fixed size

   template <typename T>
   size_t printNum(T, int base = DEC);
   size_t printNumFloat(double num, int digits = 2);             // send a double number

   // Print with print() and automaticly adding "\r\n"
   size_t println(void);                                 // print a new line
   size_t println(char c);
   size_t println(const char *s, size_t size = -1);

   template <typename T>
   size_t printlnNum(T num, int base = DEC);
   size_t printlnNumFloat(double num, int digits = 2);

   // Print data with addion a special character or string
   size_t printSpecial(const char *s, char del='\0');    // Print with delimiter at last of string
   size_t printSpecial(const char *s, const char *s2);   // adding another string
   size_t printString(const char *s);                    // Adding NULL terminater at last

   size_t available();
   // Reading from serial port
   char read();
   char peek();
   size_t readString(char *s);
   size_t readString(char *s, unsigned char pos);
   size_t readStringUntil(char *s, char del='\0');
   size_t readStringFromTo(char *s, const unsigned char tail, const unsigned char head='\0');
   size_t readStringFromIndexTo(char *s, unsigned char index, unsigned char pos);

   // Print number directly
   size_t writeBytes(unsigned char num);
   size_t writeBytes(int num);
   size_t writeBytes(unsigned int num);
   size_t writeBytes(long num);
   size_t writeBytes(unsigned long num);
   size_t writeBytes(double num);

   // Read writeBytes
   size_t readBytes(unsigned char &num);
   size_t readBytes(int &num);
   size_t readBytes(unsigned int &num);
   size_t readBytes(long &num);
   size_t readBytes(unsigned long &num);
   size_t readBytes(double &num);

private:

   char readTimeOut();                                      // read with time out
   size_t printNumber(unsigned long n, int base);           // convert number to character
   size_t printFloat(double num, unsigned char digits);
   size_t writeNumber(double num, unsigned char type);      // send number directly, breaking to union _data[]
   size_t readNumber(_data &dt, int type);


};

template <typename T>
size_t Uart::printNum(T num, int base) {
	if (base == 0) {
		return write(num);
	} else if (base == 10) {
		if (num < 0) {
			unsigned char t = print('-');
			num = -num;
			return (unsigned long)printNumber(num, 10) + t;
		}
		return (unsigned long)printNumber(num, 10);
	} else {
		return (unsigned long)printNumber(num, base);
	}
}

template <typename T>
size_t Uart::printlnNum(T num, int base) {
   size_t n = printNum(num, base);
   n += println();
   return n;

}

#endif

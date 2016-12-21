#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>
#include <string.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BUFF_SIZE 33 // will getting error if BUFF_SIZE > 100 (currently test is 199)

class Uart {

public :
   Uart(unsigned long BAUDRATE=9600);
   size_t write(char c);
   size_t write(const char *s, size_t size);

   // Print data to the serial port as human-readable ASCII text
   size_t print(char c);                                 // send a character
   size_t print(const char *s);                          // send string
   size_t print_size(const char *s, size_t size);             // send string with fixed size
   size_t print_unsigned_char(unsigned char num, int base = DEC);      // semd a char number
   size_t print_int(int num, int base = DEC);                // send an int number
   size_t print_unsigned_int(unsigned int num, int base = DEC);       // send an unsigned int number
   size_t print_long(long num, int base = DEC);               // send an int number
   size_t print_unsigned_long(unsigned long num, int base = DEC);      // send an int number
   size_t print_double(double num, int digits = 2);             // send a double number

   // Print with print() and automaticly adding "\r\n"
   size_t println(void);                                 // print a new line
   size_t println(char c);
   size_t println(const char *s);
   size_t println_size(const char *s, size_t size);
   size_t println_unsigned_char(unsigned char num, int base = DEC);
   size_t println_int(int num, int base = DEC);
   size_t println_unsigned_int(unsigned int num, int base = DEC);
   size_t println_long(long num, int base = DEC);
   size_t println_unsigned_long(unsigned long num, int base = DEC);
   size_t println_double(double num, int digits = 2);

   // Print data with addion a special character or string
   size_t printSpecial(const char *s, char del='\0');    // Print with delimiter at last of string
   size_t printSpecial(const char *s, const char *s2);   // adding another string
   size_t printString(const char *s);                    // Adding NULL terminater at last

   // Print number
   size_t write_unsigned_char(unsigned char num);
   size_t write_int(int num);
   size_t write_unsigned_int(unsigned int num);
   size_t write_long(long num);
   size_t write_unsigned_long(unsigned long num);
   size_t write_float(float num);

   //
   size_t available();
   // Reading from serial port
   char read();
   char peek();
   size_t readString(char *s);
   size_t readString(char *s, unsigned char pos);
   size_t readStringUntil(char *s, char del='\0');
   size_t readStringFromTo(char *s, const unsigned char tail, const unsigned char head='\0');
   size_t readStringFromIndexTo(char *s, unsigned char index, unsigned char pos);

private:
   size_t printNumber(unsigned long n, int base);
   size_t printFloat(double num, unsigned char digits);
   size_t writeNum(float num, unsigned char type);
   char readTimeOut();

   union _data {
      char b[4];
      double num;
   };

};

#endif

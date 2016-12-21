#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>
#include <string.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

#define CHAR 1
#define INT 2
#define LONG 4
#define FLOAT 4
#define DOUBLE 8

#define BUFF_SIZE 33 // will getting error if BUFF_SIZE > 100 (currently test is 199)
#define DEBUG_TX 0
#define DEBUG_RX 1

union _data_hex {
   char b[2];
   int hex;
};

union _data_int {
   char b[4];
   long num;
};

union _data_float {
   char b[8];
   double num;
};

class Uart {

public :
   Uart(unsigned long BAUDRATE = 9600);
   size_t write(char c);
   size_t write(const char *s, size_t size);

   // Print data to the serial port as human-readable ASCII text
   size_t print(char c);                                 // send a character
   size_t print(const char *s);                          // send a string
   size_t print(const char *s, size_t size);             // send a string with fixed size
   size_t print(unsigned char num, int base = DEC);      // semd a char number
   size_t print(int num, int base = DEC);                // send an int number
   size_t print(unsigned int num, int base = DEC);       // send an unsigned int number
   size_t print(long num, int base = DEC);               // send a long number
   size_t print(unsigned long num, int base = DEC);      // send an unsigned long number
   size_t print(double num, int digits = 2);             // send a double number

   // Print with print() and adding "\r\n" automaticlly
   size_t println(void);                                 // print a new line
   size_t println(char c);
   size_t println(const char *s);
   size_t println(const char *s, size_t size);
   size_t println(unsigned char num, int base = DEC);
   size_t println(int num, int base = DEC);
   size_t println(unsigned int num, int base = DEC);
   size_t println(long num, int base = DEC);
   size_t println(unsigned long num, int base = DEC);
   size_t println(double num, int digits = 2);

   // Print data with addion a special character or string
   size_t printSpecial(const char *s, char delim='\0');    // Print until get delimiter
   size_t printSpecial(const char *s, const char *s2);   // adding another string
   size_t printString(const char *s);                    // Adding NULL terminater at last

   size_t available();
   // Reading from serial port
   char read();
   char peek();
   size_t readString(char *s);
   size_t readString(char *s, unsigned char size);
   size_t readStringUntil(char *s, char delim='\0');
   size_t readStringFromTo(char *s, const char tail, const char head='\0');
   size_t readStringFromIndexTo(char *s, unsigned char index, unsigned char pos);

   // Print number directly
   size_t writeBytes(char *dt, size_t size = 0);
   size_t writeBytes(int *dt, size_t size = 0);
   size_t writeNumber(char num);
   size_t writeNumber(unsigned char num);
   size_t writeNumber(int num);
   size_t writeNumber(unsigned int num);
   size_t writeNumber(long num);
   size_t writeNumber(unsigned long num);
   size_t writeNumber(float num);
   size_t writeNumber(double num);

   // Read writeNumber
   size_t readBytes(char *dt, size_t size = BUFF_SIZE-1);
   size_t readBytes(int *dt, size_t size = BUFF_SIZE-1);
   size_t readNumber(char &num);
   size_t readNumber(unsigned char &num);
   size_t readNumber(int &num);
   size_t readNumber(unsigned int &num);
   size_t readNumber(long &num);
   size_t readNumber(unsigned long &num);
   size_t readNumber(float &num);
   size_t readNumber(double &num);

private:

   char readTimeOut();                                      // read with time out
   size_t printNumber(unsigned long n, int base);           // convert number to character
   size_t printFloat(double num, unsigned char digits);

};

#endif

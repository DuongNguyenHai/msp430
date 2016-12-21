### Nguyen Hai Duong
### Nov 20 2016

version 0.1
-----------

Uart library for msp430 was modified from energia/arduino source code and adding
more some useful function. Almost function has the same name with function in
energia/arduino will have the same functionality. The purpose of this library is
reduce as much as size memory of program and increasing speed of executing.
There are functions from energia/arduino which were cut off and there are some
extend functionalities added in the old functions.

There's only a buffer for RX. The reason is to save RAM of msp430. Therefore,
data will be send directly to transmit register. In the case of sending many
bytes, the program will have to wait until all bytes have transmitted.

### API

###### A : print() and println()

1. size_t print(data)

-  Print data to the serial port as human-readable ASCII text. The data can be :
   char/char * /unsigned char/int/unsinged int/long/unsinged long/float/double
   Notice : string data was cut '\0' off automatically and print. Print
   float/double is heavily work. Its allocated about 3kb memory.
-  Return the number of bytes written.

2. size_t print(data, int base)

-  Print number data with special base : BIN, DEC, HEX, OCT. For floating point
   number, the option specifies the number of decimal places to use.

-  example :
   print(78, BIN) gives "1001110"
   print(78, OCT) gives "116"
   print(78, DEC) gives "78"
   print(78, HEX) gives "4E"
   println(1.23456, 0) gives "1"
   println(1.23456, 2) gives "1.23"
   println(1.23456, 4) gives "1.2346"

-  Return the number of bytes written.

3. size_t print(const char * s, size_t size)

-  Print string with fixed size.
-  Return the number of bytes written.

4. size_t println(data) / println(void) /
   println(data, int base) / println(const char * s, size_t size)

-  print data and adding "\r\n" at the end of data. This function should only use
   for debug.
-  Return the number of bytes written.

5. size_t printSpecial(const char * s, char del='\0' )

-  Print a part of string from head of string to delimiter. Default of delimiter
is null terminator.
-  Example : print("hello guys!",'o') will print "hell";
-  Return the number of bytes written.

6. size_t printSpecial(const char * s, const char * s2)

-  Print 2 string in one command. String 2 was append to string one.
-  Return the number of bytes written.

7. size_t printString(const char * s)

-  Print string with adding '\0' at the end of string.
-  Return the number of character/byte written.

##### B : available() and readstring()

8. size_t available()

-  Return the number of bytes available for reading in buffer

9. size_t readString(char * s)

-  Reading characters in buffer and save it to char * s. The function will
   terminate if it get '\0' character or get timeout.
-  Return the number of characters has read.

10. size_t readString(char * s, unsigned char size)

-  Reading size characters (number of characters) in buffer. It also terminates
   if it get '\0' and timeout. Then saving characters has read to s.
-  Example : assume that string in buffer is "Hello man"
             int n = readString(s, 5);
             will return n = 5 and string s = "Hello"
-  Return the number of characters has read.

11. size_t readStringUntil(char * s, char del='\0')

-  Reading characters in buffer until delimiter character. It also terminates
   if it get '\0' and timeout. Then saving characters has read to s.
-  Return the number of characters has read.

12. size_t readStringFromTo(char * s, const char tail, const char head='\0').

-  Reading characters between tail character and head character. It also
   terminates if it get '\0' and timeout. Then saving characters has read to s.
-  Example :   assume that string in buffer is "Hello man"
               int n = readStringFromTo(s, 'H', 'o');
               will return n = 3 and string s = "ell"
-  Return the number of characters has read.

13. size_t readStringFromIndexTo(char * s, unsigned char index, unsigned char pos)

-  Reading characters from index to fixed position. It also terminates if it
   get '\0' and timeout. Then saving characters has read to s.
-  Example : assume that string in buffer is "Hello man"
             int n = readStringFromIndexTo(s, 1, 5);
             will return n = 6 and string s = "Hello"
-  Return the number of characters has read.            

##### C : write() and read()

14. size_t write(char c)

-  Write a byte data.
-  Return 1.

15. size_t write(const char * s, size_t size)

-  Write array of character with fixed size.
-  Return number of bytes which were transmitted.

16. char read()

-  Read a single byte from buffer.
-  Return byte value.

##### D : writeBytes() and readBytes()

17. size_t writeBytes(char * dt, size_t size = 0)

-  Write an array of char with fixed size.
-  Return the number of bytes written.

18. size_t writeBytes(int * dt, size_t size = 0)

-  Write an array of int with fixed size.
-  Return the number of bytes written.

19. size_t readBytes(char * dt, size_t size = BUFF_SIZE-1)

-  Read size bytes and save to char array.
-  Return the number of bytes has read.

20. size_t readBytes(int * dt, size_t size = BUFF_SIZE-1)

-  Read size bytes and save to int array.
-  Return the number of bytes has read.

##### E : writeNumber() and readNumber()

21. size_t writeNumber(number)

-  Breaking number into bytes and transmit them. Number can be char/unsinged char/
   int/unsigned int/long/unsigned long/float/double.
-  Return the number of bytes written. char/unsinged char will return 1, int/unsigned
   int will return 2, long/unsigned long/float will return 4, double will return 8.
-  Notice : its a fast and lightweight function.

22. size_t readNumber(&num)

-  Reading number. It can only be used if number was transmitted by writeNumber()
   function. If writeNumber() send a integer value, readNumber() should read a integer
   value too (its mean "num" was integer).

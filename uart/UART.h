////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY UART
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Version : 1.0	14/10/2014
// Email:	phthuanbk55@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// MSP430x2xx LIBRARY
//******************************************************************/

#ifndef _UART_H_
#define _UART_H_

#include <msp430g2553.h>

extern unsigned long SMCLK_F;                 // frequency of Sub-System Master Clock in Hz
extern unsigned long BAUDRATE;                   // may be ... 1200, 2400, 4800, 9600, 19200, ...


//*****************************************************************************
// Bien toan cuc
//*****************************************************************************

/*
 * Cac ky tu dac biet
 * 	0 Ky tu rong
 * 	1 Bat dau header
 * 	2 Bat dau van ban
 * 	3 Ket thuc van ban
 * 	4 Ket thuc truyen
 * 	5 Truy van
 * 	7 Tab ngang
 * 	8 Xoa nguoc
 * 	9 Tab ngang
 * 	10 Xuong dong
 * 	11 Tab doc
 */
/*******************************************************************************
*  FCS calculation function
********************************************************************************/
unsigned char calcFCS(unsigned char *pMsg, unsigned char len); 

//*****************************************************************************
// Transfer  UART
//*****************************************************************************
void UART_Init(unsigned long BAUDRATE);						       	//Khoi tao UART
void UART_Write_Char(unsigned char data);	   	//Gui ki tu
void UART_Write_String(char* string);		  	//Gui chuoi ki tu
void UART_Write_Int(unsigned long n);		   	//Goi so kieu int
void UART_Write_Reg(char *name, int n);			//In ra gia tri bit cua thanh ghi
void UART_Write_Float(float x,unsigned char coma);		//coma<=4
//In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma
//*****************************************************************************
// Receive  UART
//*****************************************************************************
char UART_Read_Char();							//Nhan ki tu
void UART_Read_String(char *s);					//Nhan chuoi ky tu
char UART_Data_Ready();							//Kien tra module san sang

#endif	/* _UART_H_ */

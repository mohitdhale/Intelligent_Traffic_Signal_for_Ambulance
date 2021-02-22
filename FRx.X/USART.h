/* 
 * File:   USART.h
 * Author: Nilesh Mundphan
 *
 * Created on December 21, 2014, 9:18 PM
 */
#ifndef USART_H
#define	USART_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif
//Constants
#define RECEIVE_BUFF_SIZE 64
//Varriables
volatile char URBuff[RECEIVE_BUFF_SIZE];	//USART Receive Buffer
volatile int8_t UQFront;
void sig();
volatile int8_t UQEnd;
void USARTInit(uint16_t baud_rate);
void USARTWriteChar(char ch);
void USARTWriteString(const char *str);
void USARTWriteLine(const char *str);
void USARTHandleRxInt();
char USARTReadData();
uint8_t USARTDataAvailable();
void USARTGotoNewLine();
void USARTReadBuffer(char *buff,uint16_t len);
void USARTFlushBuffer();
#ifdef	__cplusplus
}
#endif
#endif	/* USART_H */


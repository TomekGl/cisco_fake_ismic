/** \file usart.h
 * \addtogroup usart
 * \brief UART
 *
 *
 * \author Tomasz Głuch, http://tomaszgluch.pl/
 * \date 2012-12-31
 */

#ifndef USART_H_
#define USART_H_
#include <stdint.h>

void UART0_Init(unsigned int baud_rate);
void UART0_Read(void);
void UART0_Write(char value);
void UART0_Write_Text(char msg[]);
void UART0_WriteBinary(uint8_t *ptr, int len);

uint8_t UART0_GetByte(void);
uint8_t UART0_RxBufferStatus(void);

#define U0LCR_DLAB 1<<7
#define U0LCR_SetBreak 1<<6
#define U0LCR_StickParity 1<<5
#define U0LCR_EvenParity 1<<4
#define U0LCR_ParityEnable 1<<3
#define U0LCR_2StopBits 1<<2
#define U0LCR_8Bits 3


#define U0IIR_RLS	3
#define U0IIR_RDA	2
#define U0IIR_CTI	6
#define U0IIR_THRE	1


#endif /* USART_H_ */

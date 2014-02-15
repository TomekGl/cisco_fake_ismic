/** \file usart.c
 *  \addtogroup usart
 *
  * \author Tomasz Głuch, http://tomaszgluch.pl/
 * \date 2012-12-31
 */
#include <stdint.h>
#include <stdio.h>

#include "inc/LPC214x.h"
#include "config.h"
#include "buffers.h"
#include "usart.h"

/// RX circular buffer
volatile Tcircle_buffer UART_buffer_RX;
/// TX circular buffer
volatile Tcircle_buffer UART_buffer_TX;

volatile uint8_t UART0_TX_idle;

void UART0_IRQHandler(void) __attribute__ ((interrupt("IRQ")));
void UART0_StartSending(Tcircle_buffer *buffer);

void UART0_Write(char value)
{
	buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, value);
	UART0_StartSending((Tcircle_buffer *)&UART_buffer_TX);
//	//wait for transmitter ready
//	while(!(U0LSR&0x20));                        //THRE = 0 stay here
//	U0THR = value;
}

void UART0_WriteInteger(unsigned int val) {
	char buf[13];
	char *bufptr;
	itoa(val, buf, 10);
	bufptr=&buf;
	while(*bufptr) {
		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, *bufptr++);
	}
	UART0_StartSending((Tcircle_buffer *)&UART_buffer_TX);
}


void UART0_WriteBinary(uint8_t *ptr, int len) {
	char buf[6];
	char *bufptr;
	while (len--) {
		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, ' ');
//		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, '0');
//		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, 'x');
		itoa(*ptr++, buf, 16);
		bufptr=&buf;
		while(*bufptr) {
			buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, *bufptr++);
		}
	}
	UART0_StartSending((Tcircle_buffer *)&UART_buffer_TX);
}

void UART0_Write_Text(char msg[])
{
	while(*msg) {
		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, *msg);
		msg++;
	}
	UART0_StartSending((Tcircle_buffer *)&UART_buffer_TX);
}

void UART0_StartSending(Tcircle_buffer *buffer) {
	if (UART0_TX_idle && buf_getcount(buffer)) {
		//while(!(U0LSR&0x20));                        //THRE = 0 stay here
		UART0_TX_idle = 0;
		U0THR = buf_getbyte(buffer);
	}
}

uint8_t UART0_GetByte(void) {
	while (!buf_getcount((Tcircle_buffer *)&UART_buffer_RX));
	return buf_getbyte((Tcircle_buffer *)&UART_buffer_RX);
}

uint8_t UART0_RxBufferStatus(void) {
	return buf_getcount((Tcircle_buffer *)&UART_buffer_RX);
}

void UART0_Read() {
	while (buf_getcount((Tcircle_buffer *)&UART_buffer_RX)) {
		buf_putbyte((Tcircle_buffer *)&UART_buffer_TX, buf_getbyte((Tcircle_buffer *)&UART_buffer_RX)-'a'+'A');
	}
}

/** \function UART0_Init(unsigned int baud_rate)
 * \param baud_rate Baud rate
 * \brief Initialize UART0 with given baudrate, 8N1
 */
void UART0_Init(unsigned int baud_rate) {

	//initialize buffers
    buf_init((Tcircle_buffer *)&UART_buffer_TX);
    buf_init((Tcircle_buffer *)&UART_buffer_RX);
    UART0_TX_idle = 1;

	PINSEL0 |= 0x00000005;                //P0.0 as TX0 and P0.1 as RX0
	U0LCR = U0LCR_DLAB | U0LCR_8Bits; //Enable access to Divisor Latches

	//Baud_Rate = PCLK*MulVal / [(16*(256*U0DLM+U0DLL)*(MulVal + DivAddVal))]

	U0FDR = 14<<4|1; //Mulval=14, DivAddVal=1
	U0DLM = 0x00;
	U0DLL = 19; //81;
	U0LCR = U0LCR_8Bits; //Disable Access to Divisor Latches

	/* interrupts */
	//All interrupts assigned to IRQ
	VICIntSelect = 0;
	//Assign handler to vector 2
	VICVectAddr2 = (unsigned int) UART0_IRQHandler;
	VICVectCntl2 = 6 | 0x20;
	//Enable
	VICIntEnable |= 1<<6;

	U0IER = 1<<0 | 1<<1 ; // Receive Data Available | THRE

}

/** \function UART0_IRQHandler(void)
 * \brief UART0 Interrupt Handler
 */
void UART0_IRQHandler(void)  {
	uint32_t status = (U0IIR>>1)&0x7; //interrupt identification

	switch(status) {
	case U0IIR_RLS:
		//error
		status = U0LSR; //dummy read to clear int.
		break;
	case U0IIR_RDA: //data available
		buf_putbyte((Tcircle_buffer *)&UART_buffer_RX, U0RBR);
		break;
	case U0IIR_THRE: //ready to send
		if (buf_getcount((Tcircle_buffer *)&UART_buffer_TX)) {
			U0THR = buf_getbyte((Tcircle_buffer *)&UART_buffer_TX);
		} else {
			UART0_TX_idle = 1;
		}
		break;
	}
	VICVectAddr = 0; //Dummy write
}


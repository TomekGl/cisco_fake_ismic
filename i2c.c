/** \file i2c.c
 * \brief Interrupt-driven I2C bus support
 * \details This module provides support of I2C bus on LPC2131/2/4/6/8 microcontrollers.
 *
 *
 * This file holds a very basic ARM code for LPC2103. This code
 * initializes the Fast GPIOs, starts the MAM (Memory Acceleration Module) and
 * enables the PLL to achieve the highest allowed frequency for LPC2103 (72MHz).
 * Main code block just blinks the LED. The LED port and pin are defined in
 * config.h file. Target core frequency and quartz crystal resonator
 * frequency are defined there as well.
 *
 * \author Tomasz Głuch, http://tomaszgluch.pl/
 * \date 2012-12-31
 */



#include <stdio.h>
#include <string.h>

#include "inc/LPC214x.h"
#include "usart.h"
#include "i2c.h"
#include "ismic.h"


void I2C_IRQHandler(void) __attribute__ ((interrupt("IRQ")));


static volatile uint8_t status;

static volatile uint8_t SlaveRcv;
static volatile uint8_t RcvFlag, SndFlag;

/* slave vars */
static volatile uint8_t recvBuffer[4];
static volatile uint8_t recvPointer;
static volatile uint8_t recvCounter;
static volatile uint8_t sendBuffer[4];
static volatile uint8_t sendPointer;
static volatile uint8_t sendCounter;
uint8_t i2cAddress;

void I2C_DebugPrint() {
	UART0_Write('0' + sendPointer);
	UART0_Write('.');
	UART0_Write('0' + sendCounter);
	UART0_Write_Text("\r\n");
	UART0_Write('0' + recvPointer);
	UART0_Write('.');
	UART0_Write('0' + recvCounter);
	UART0_Write_Text("\r\n");
	UART0_Write_Text((char *) &recvBuffer);
}

void I2C_Query() {
	i2cAddress = I2C_LM75_ADDRESS;
	sendBuffer[0] = 0;
	sendCounter = 1;
	sendPointer = 0;
	recvPointer = 0;
	recvCounter = 2;
	I20CONSET = STA;
	unsigned int timeout = 50000;
	while (recvPointer!=recvCounter) {
		if (0 == timeout--) {
			UART0_Write_Text("I2C Timeout!\r\n");
			return;
		}
	}
	I2C_DebugPrint();
}

void I2C_Init() {
	/* I2C */
	PINSEL0 |= 0x50;
	/* Initialize I 2 C */
	I20SCLH = 62;
	I20SCLL = 63;
	/* 100 KHz */

	I20CONCLR = 0x6c; //STA | STO | SI | AA;
	/* clearing all flags */

	//Own address in slave mode
	I20ADR = I2C_OWN_ADDRESS<<1;

	I20CONSET = I2EN | AA;
	/* enabling I2C - master and slave*/


	//Wektor 1
	VICVectAddr0 = (unsigned long) I2C_IRQHandler;
	VICVectCntl0 = 9 | 1<<5;
	VICIntEnable |= 1 << 9; //I2C0

	VICSoftIntClr = 1<<9;

}

/*************************** MAIN ************************/
/********************** I 2 C ISR **************************/

void I2C_IRQHandler(void) {
	uint8_t buf[8];
	int temp = 0;
	temp = I20STAT;
	status = temp;
#ifdef DEBUG
	UART0_Write(status);
#endif
	switch (temp) {
	/* master states */
	case 0x08:
		I20DAT = i2cAddress<<1 | I2C_Write;
		I20CONSET = AA;
		I20CONCLR = SI|STA;
		break;
	case 0x10: //repeated start
		I20DAT = i2cAddress<<1 | I2C_Read;
		I20CONSET = AA;
		I20CONCLR = SI|STA;
		break;

	/* master transmitter */
	case 0x18: //send first byte
			I20DAT = sendBuffer[sendPointer++];
			I20CONSET = AA;
			I20CONCLR = SI;
		break;
	case 0x28: //send consecutive bytes or send repeated start after last byte
		if (sendPointer<sendCounter) {
			I20DAT = sendBuffer[sendPointer++];
			I20CONSET = AA;
			I20CONCLR = SI;
		} else {
			I20CONSET = STA;
			I20CONCLR = SI;
		}
		break;
	case 0x20: //NACK received after slave address,  stop
		I20CONSET = STO | AA;
		break;

	/* master receiver */
	case 0x40: //ACK received for slave address
		I20CONSET = AA;
		I20CONCLR = SI;
		break;
	case 0x50: //data received
		recvBuffer[recvPointer++] = I20DAT;
		if (recvPointer<recvCounter-1) {
			I20CONSET = AA; //send ACK
		} else {
			I20CONCLR = AA;
		}
		break;
	case 0x58: //data received with NACK
		recvBuffer[recvPointer++] = I20DAT;
		I20CONSET = STO | AA;
		break;

	/* slave states */
	case 0x60:				// own SLA+W received, Ack returned (slave receiver)
		I20CONSET = AA;
		break;
	case 0x68:				// Addressed as slave
		I20CONSET = AA|STA;				// set AA, return ACK on first byte
		break;
	case 0x80:				// Data received, ACK returned
		SlaveRcv = I20DAT; //read and store data, NACK on next byte
		I20CONSET = AA;
		if (!bankSet) {
			bankByteIndex = 0;
			bankNumber = SlaveRcv;
			UART0_Write_Text("\r\nBank ");
			itoa(bankNumber, buf, 10);
			UART0_Write_Text(buf);
			bankSet = 1;
		} else {
			if (bankByteIndex < bank_size[bankNumber]) {
				banks[bankNumber][bankByteIndex++] = SlaveRcv;	// Transmit last data AA = 0
			} else if (bankByteIndex == bank_size[bankNumber]) {
				bankByteIndex++;
				//checksum, ignore it
				RcvFlag = bankNumber; //mark write as finished
				UART0_Write_Text(" written:");
				UART0_WriteBinary(&(banks[bankNumber][0]), bank_size[bankNumber]);
				UART0_Write_Text("\r\n");
			} else {
				//next bytes are attempts to write beyond bank
				//UART0_Write('!');
			}
		}
		break;
	case 0x88:	// data received, NACK returned
	case 0xA0:	// STOP or REP.START received while addressed as slave
	case 0xC0:	// Data transmitted, NOT ACK received
	case 0xC8:	// Last data transmitted, ACK received
		I20CONSET = AA;	// set AA, switch to not addressed slave mode
		bankSet = 0;
		break;
	case 0xA8:	// own SLA+R received, Ack returned (slave transmitter)
	case 0xB8:	// Data transmitted, ACK received
		if (bankByteIndex < bank_size[bankNumber]) {
			I20DAT = banks[bankNumber][bankByteIndex++];	// Transmit last data AA = 0
		} else if (bankByteIndex == bank_size[bankNumber]) {
			I20DAT = BankCRC(banks[bankNumber], bank_size[bankNumber]);
			SndFlag = bankNumber;
			UART0_Write_Text(" read:");
			UART0_WriteBinary(&(banks[bankNumber][0]), bank_size[bankNumber]);
			UART0_Write_Text("\r\n");
		} else {
			I20DAT = 0xaa;
		}
		I20CONSET = AA;
		break;
	default:
		I20CONCLR = AA|STA|STO|SI;
		UART0_Write(temp);
		UART0_Write_Text("Wtf\r\n");
		break;
	}

	I20CONCLR = SI; /* clear interrupt SI*/
	VICVectAddr = 0xFF; /* dummy write to signal end interrupt handler */
}

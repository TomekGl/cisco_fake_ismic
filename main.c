/** \file main.c
 * \brief Cisco fake ISMIC controller
 *
 * \author Tomasz Głuch, http://tomaszgluch.pl/
 * \date 2012-12-31
 */

/******************************************************************************
 * project: cisco_fake_ismic
 * chip: LPC2103
 * compiler: arm-none-eabi-gcc version 4.7.4 20130613 (release)
 * [ARM/embedded-4_7-branch revision 200083]
 *
 *
 * prefix: (none)
 *
 * available global functions:
 * 	int main(void)
 *
 * available local functions:
 * 	static void mam_start(uint32_t frequency)
 * 	static void pll_feed(void)
 * 	static uint32_t pll_start(uint32_t crystal, uint32_t frequency)
 * 	static void system_init(void)
 *
 * available interrupt handlers:
 ******************************************************************************/

/*
 +=============================================================================+
 | includes
 +=============================================================================+
 */

#include <stdint.h>
#include "inc/LPC214x.h"
#include "config.h"
#include "hardware.h"
#include "armint.h"
#include "usart.h"
#include "i2c.h"
#include "ismic.h"
/*
 +=============================================================================+
 | module variables
 +=============================================================================+
 */

#define TIMER0_VIC (1<<4)
#define TIMER0_VIC_BIT 4

#define TIMER1_VIC (1<<5)
#define TIMER1_VIC_BIT 5

#define VIC_IRQSLOT_EN (1<<5)

#define T0MCR_Interrupt_on_MR0 1<<0
#define T0MCR_Interrupt_on_MR1 1<<3
#define T0MCR_Reset_on_MR0 0x2U
#define T0TCR_Counter_Reset 0x2U
#define T0TCR_Counter_Enable 0x1U
#define T0IR_MR0 1<<0
#define T0IR_MR1 1<<1

#define T1MCR_Interrupt_on_MR1 1<<3
#define T1MCR_Reset_on_MR1 1<<4
#define T1TCR_Counter_Reset 0x2U
#define T1TCR_Counter_Enable 0x1U
#define T1IR_MR1 1<<1


//Przerwanie wektoryzowane IRQ
void IrqTimer0Handler(void) __attribute__ ((interrupt("IRQ")));
void IrqTimer1Handler(void) __attribute__ ((interrupt("IRQ")));

static volatile unsigned int SystemClock;
static volatile uint8_t SystemClockFlag10Hz;

static volatile uint8_t stan;
static volatile unsigned int pwm;


/*
 +=============================================================================+
 | local functions' declarations
 +=============================================================================+
 */


/*
 +=============================================================================+
 | global functions
 +=============================================================================+
 */

/*------------------------------------------------------------------------*//**
 * \brief main code block
 * \details Call some static initialization functions and blink the led with
 * frequency defined via count_max variable.
 *//*-------------------------------------------------------------------------*/

int main(void) {
	//vectors in flash, fast GPIO
	system_init();
	//use PLL
	pll_start(CRYSTAL, FREQUENCY);

	//enable front LEDs
	LED_CLR = LED | LED2;
	//disable shutdown
//	LED_CLR = POWER;
	//configure as outputs
	LED_DIR |= LED | LED2 | POWER | (1<<14);
LED_SET = 1<<14;
	//initialize UART0, debugging
	UART0_Init(9600);
	UART0_Write_Text("Start\r\n");
	while(1) ;

	//Timer 0, as system clock source
	//Prescale register, interval 100kHz at 25MHz
	T0PR = 1; //(PCLK cycles - 1) to increment TC
	//Reset when MR0=TC0, IRQ
	T0MCR |= T0MCR_Interrupt_on_MR0 | T0MCR_Interrupt_on_MR1| T0MCR_Reset_on_MR0;

	T0MR1 = 100;
	//Reset on TC=10
	T0MR0 = 255;
	//Reset timer & prescale counters
	T0TCR = T0TCR_Counter_Reset;
	//Enable T0
	T0TCR = T0TCR_Counter_Enable;


//	//Timer 1, as PWM on P0.14
//	//Prescale register, interval 10kHz at 25MHz
//	T1PR = 250000-1; //(PCLK cycles - 1) to increment TC
//	//Reset when MR1=TC, IRQ
//	T1MCR |= T1MCR_Interrupt_on_MR1 | T1MCR_Reset_on_MR1;
//	//Reset on:
//	T1MR1 = 10;
//	//Reset timer & prescale counters
//	T1TCR = T1TCR_Counter_Reset;
//	//Enable T1
//	T1TCR |= T1TCR_Counter_Enable;


	/* interrupts */
	VICIntSelect = 0; //All interrupts assigned to IRQ
	//Vector 1 -> Timer0
	VICVectAddr1 = (unsigned int) IrqTimer0Handler;
	VICVectCntl1 = TIMER0_VIC_BIT | VIC_IRQSLOT_EN;
	VICIntEnable |= TIMER0_VIC;

//	//Vector 3 -> Timer0
//	VICVectAddr3 = (unsigned int) IrqTimer1Handler;
//	VICVectCntl3 = TIMER1_VIC_BIT | VIC_IRQSLOT_EN;
//	VICIntEnable |= TIMER1_VIC;

	I2C_Init();

	//SEI
	enable_irq();

	LED_SET = LED2;

	UART0_Write_Text("Running\r\n");

	uint8_t c;
	while(1)
	{
//		if (SystemClockFlag10Hz>0) {
//			SystemClockFlag10Hz=0;
//			//FIO0MASK = ~(LED|LED2);
//			FIO0PIN ^= LED2;
//		}
		if (UART0_RxBufferStatus()) {
			c = UART0_GetByte();
			switch (c) {
			case 'c':
				I2C_Query();
				UART0_Write_Text("Start\r\n");
				break;
			case 'p':
				I2C_DebugPrint();
				break;
			case 'o':
				FIO0DIR |= 1 << 14;
				FIO0SET = 1 << 14;
				break;
			case 'O':
				FIO0DIR |= 1 << 14;
				FIO0CLR = 1 << 14;
				break;
			case 'i':
				FIO0DIR &= ~(1 << 14);
				break;
			case '+':
				T0MR1 = (T0MR1<246)?T0MR1+10:255;
				break;
			case '-':
				T0MR1 = (T0MR1>9)?T0MR1-10:0;
				break;
			case 'q':
				UART0_WriteInteger(T0TC);
				break;
			case 'w':
				UART0_WriteInteger(SystemClock);
				break;
			case 'e':
				UART0_WriteInteger(SystemClock % 10);
				break;
			case '=':
				UART0_WriteInteger(T1TC);
				break;
			case 'P':
				pwm = 100;
				break;

			default:
				if (!(c < '0' || c > '9')) {
					UART0_Write_Text("Register: ");
					UART0_Write(c);
					UART0_Write_Text("\r\n");
					UART0_Write_Text(banks[c - '0']);
					UART0_Write_Text("\r\n");
				}
				break;
			}
		}
	}
}
/*
 +=============================================================================+
 | local functions
 +=============================================================================+
 */


/*
 +=============================================================================+
 | ISRs
 +=============================================================================+
 */

void IrqTimer0Handler(void) {
	if (T0IR&T0IR_MR0) { //reset
		FIO0CLR = LED;
		FIO0CLR = 1<<14;
		T0IR = T0IR_MR0;
	}
	if (T0IR&T0IR_MR1) { //pwm
		if (T0MR1<255) {
			FIO0SET = LED;
			FIO0SET = 1<<14;
		}
		T0IR = T0IR_MR1;
	}

	//SystemClock++;
	//FIO0MASK = ~(LED|LED2);
//	if (0 == SystemClock%10000) {
//		SystemClockFlag10Hz = 1;
//	}


	//Dummy write
	VICVectAddr = 0;
}

/******************************************************************************
 * END OF FILE
 ******************************************************************************/

/** \file main.c
 * \brief Sample ARM project
 * \details This file holds a very basic ARM code for LPC2103. This code
 * initializes the Fast GPIOs, starts the MAM (Memory Acceleration Module) and
 * enables the PLL to achieve the highest allowed frequency for LPC2103 (72MHz).
 * Main code block just blinks the LED. The LED port and pin are defined in
 * config.h file. Target core frequency and quartz crystal resonator
 * frequency are defined there as well.
 *
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
 * project: cisco_fake_ismic
 * chip: LPC2131
 * compiler: arm-none-eabi-gcc version 4.7.4 20130613 (release)
 * [ARM/embedded-4_7-branch revision 200083]
 *
 *
 * prefix: (none)
 *
 * available global functions:
 * 	static void mam_start(uint32_t frequency)
 * 	static void pll_feed(void)
 * 	static uint32_t pll_start(uint32_t crystal, uint32_t frequency)
 * 	static void system_init(void)
 *
 * available interrupt handlers:
 ******************************************************************************/

#include <stdint.h>
#include "inc/LPC214x.h"
#include "hdr/hdr_scb.h"
#include "hdr/hdr_mam.h"


/*------------------------------------------------------------------------*//**
 * \brief Start MAM
 * \details Enables the Memory Acceleration Module in LPC2103, which allows the
 * CPU to work full-speed out of Flash.
 *
 * \param [in] frequency defines the target frequency of the core
 *//*-------------------------------------------------------------------------*/

void mam_start(uint32_t frequency) {
	uint32_t latency;

	if (frequency < 20000000)	// 1 cycle latency for core speed below 20MHz
		latency = 1;
	else if (frequency < 40000000)// 2 cycle latency for core speed between 20MHz and 40MHz
		latency = 2;
	else
		// 3 cycle latency for core speed over 40MHz
		latency = 3;

	MAMTIM = latency;						// set the latency
	MAMCR = MAMCR_MODE_FULL;				// enable MAM
}

/*------------------------------------------------------------------------*//**
 * \brief PLL feed sequence
 * \details Issues a special "PLL feed sequence" which validates the changes to
 * PLL control registers
 *//*-------------------------------------------------------------------------*/

void pll_feed(void) {
	PLLFEED = PLLFEED_FIRST;
	PLLFEED = PLLFEED_SECOND;
}

/*------------------------------------------------------------------------*//**
 * \brief Starts the PLL
 * \details Configure and enable PLL to achieve some frequency with some crystal.
 * Before the speed change MAM is enabled via mam_start(). PLL parameters m and p
 * are based on function parameters. The PLL is set up, started and connected.
 * Finally, APB clock ratio is set to 1:1.
 *
 * \param [in] crystal is the frequency of the crystal resonator connected to the
 * LPC2103
 * \param [in] frequency is the desired target frequency after enabling the PLL
 *
 * \return real frequency that was set
 *//*-------------------------------------------------------------------------*/

uint32_t pll_start(uint32_t crystal, uint32_t frequency) {
	uint32_t m, p = 0, fcco;

	mam_start(frequency);		// reconfigure/enable MAM before changing speed

	m = frequency / crystal;				// M is the PLL multiplier
	fcco = m * crystal * 2;				// FCCO is the internal PLL frequency

	frequency = crystal * m;

	while (fcco < 156000000) {
		fcco *= 2;
		p++;	// find P which gives FCCO in the allowed range (over 156MHz)
	}

	PLLCFG = (m - 1) | (p << PLLCFG_PSEL_bit);	// set basic PLL parameters
	pll_feed();
	PLLCON = PLLCON_PLLE;					// enable PLL
	pll_feed();
	while (!(PLLSTAT & PLLSTAT_PLOCK))
		;		// wait for PLL lock
	PLLCON = PLLCON_PLLE | PLLCON_PLLC;		// connect PLL as the system clock
	pll_feed();

	APBDIV = APBDIV_APBDIV_2;				// set APB clock ratio to 1:1

	return frequency;
}

/*------------------------------------------------------------------------*//**
 * \brief Initialize system
 * \details Enables the Fast GPIOs and ensures the vectors are taken from Flash
 *//*-------------------------------------------------------------------------*/

void system_init(void) {
	SCS = SCS_GPIO0M;						// enable Fast I/O
	MEMMAP = MEMMAP_MAP_FLASH;				// vectors in Flash
}

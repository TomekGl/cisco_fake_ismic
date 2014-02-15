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


#ifndef HARDWARE_H_
#define HARDWARE_H_

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
void mam_start(uint32_t frequency);

/*------------------------------------------------------------------------*//**
 * \brief PLL feed sequence
 * \details Issues a special "PLL feed sequence" which validates the changes to
 * PLL control registers
 *//*-------------------------------------------------------------------------*/

void pll_feed(void);

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

uint32_t pll_start(uint32_t crystal, uint32_t frequency);
/*------------------------------------------------------------------------*//**
 * \brief Initialize system
 * \details Enables the Fast GPIOs and ensures the vectors are taken from Flash
 *//*-------------------------------------------------------------------------*/

void system_init(void);


#endif /* HARDWARE_H_ */

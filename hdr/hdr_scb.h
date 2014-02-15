/** \file hdr_scb.h
 * \brief Header with definition of bits in System Control Block registers
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* chip: LPC2101 / LPC2102 / LPC2103
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/

#ifndef HDR_SCB_H_
#define HDR_SCB_H_

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

/*
+-----------------------------------------------------------------------------+
| EXTINT - External Interrupt Flag register
+-----------------------------------------------------------------------------+
*/

#define EXTINT_EINT0_bit					0
#define EXTINT_EINT1_bit					1
#define EXTINT_EIN2_bit						2

#define EXTINT_EINT0						(1 << EXTINT_EINT0_bit)
#define EXTINT_EINT1						(1 << EXTINT_EINT1_bit)
#define EXTINT_EIN2							(1 << EXTINT_EIN2_bit)

/*
+-----------------------------------------------------------------------------+
| INTWAKE - Interrupt Wake-up register
+-----------------------------------------------------------------------------+
*/

#define INTWAKE_EXTWAKE0_bit				0
#define INTWAKE_EXTWAKE1_bit				1
#define INTWAKE_EXTWAKE2_bit				2
#define INTWAKE_RTCWAKE_bit					15

#define INTWAKE_EXTWAKE0					(1 << INTWAKE_EXTWAKE0_bit)
#define INTWAKE_EXTWAKE1					(1 << INTWAKE_EXTWAKE1_bit)
#define INTWAKE_EXTWAKE2					(1 << INTWAKE_EXTWAKE2_bit)
#define INTWAKE_RTCWAKE						(1 << INTWAKE_RTCWAKE_bit)

/*
+-----------------------------------------------------------------------------+
| EXTMODE - External Interrupt Mode register
+-----------------------------------------------------------------------------+
*/

#define EXTMODE_EXTMODE0_bit				0
#define EXTMODE_EXTMODE1_bit				1
#define EXTMODE_EXTMODE2_bit				2

#define EXTMODE_EXTMODE0					(1 << EXTMODE_EXTMODE0_bit)
#define EXTMODE_EXTMODE1					(1 << EXTMODE_EXTMODE1_bit)
#define EXTMODE_EXTMODE2					(1 << EXTMODE_EXTMODE2_bit)

/*
+-----------------------------------------------------------------------------+
| EXTPOLAR - External Interrupt Polarity register
+-----------------------------------------------------------------------------+
*/

#define EXTPOLAR_EXTPOLAR0_bit				0
#define EXTPOLAR_EXTPOLAR1_bit				1
#define EXTPOLAR_EXTPOLAR2_bit				2

#define EXTPOLAR_EXTPOLAR0					(1 << EXTPOLAR_EXTPOLAR0_bit)
#define EXTPOLAR_EXTPOLAR1					(1 << EXTPOLAR_EXTPOLAR1_bit)
#define EXTPOLAR_EXTPOLAR2					(1 << EXTPOLAR_EXTPOLAR2_bit)

/*
+-----------------------------------------------------------------------------+
| SCS - System Control and Status flags register
+-----------------------------------------------------------------------------+
*/

#define SCS_GPIO0M_bit						0

#define SCS_GPIO0M							(1 << SCS_GPIO0M_bit)

/*
+-----------------------------------------------------------------------------+
| MEMMAP - Memory Mapping control register
+-----------------------------------------------------------------------------+
*/
#define MEMMAP_MAP_bit						0
#define MEMMAP_MAP0_bit						0
#define MEMMAP_MAP1_bit						1

#define MEMMAP_MAP0							(1 << MEMMAP_MAP0_bit)
#define MEMMAP_MAP1							(1 << MEMMAP_MAP1_bit)

#define MEMMAP_MAP_BOOT_value				0
#define MEMMAP_MAP_FLASH_value				1
#define MEMMAP_MAP_RAM_value				2
#define MEMMAP_MAP_mask						3

#define MEMMAP_MAP_BOOT						(MEMMAP_MAP_BOOT_value << MEMMAP_MAP_bit)
#define MEMMAP_MAP_FLASH					(MEMMAP_MAP_FLASH_value << MEMMAP_MAP_bit)
#define MEMMAP_MAP_RAM						(MEMMAP_MAP_RAM_value << MEMMAP_MAP_bit)

/*
+-----------------------------------------------------------------------------+
| PLLCON - PLL Control register
+-----------------------------------------------------------------------------+
*/

#define PLLCON_PLLE_bit						0
#define PLLCON_PLLC_bit						1

#define PLLCON_PLLE							(1 << PLLCON_PLLE_bit)
#define PLLCON_PLLC							(1 << PLLCON_PLLC_bit)

/*
+-----------------------------------------------------------------------------+
| PLLCFG - PLL Configuration register
+-----------------------------------------------------------------------------+
*/

#define PLLCFG_MSEL_bit						0
#define PLLCFG_MSEL0_bit					0
#define PLLCFG_MSEL1_bit					1
#define PLLCFG_MSEL2_bit					2
#define PLLCFG_MSEL3_bit					3
#define PLLCFG_MSEL4_bit					4
#define PLLCFG_PSEL_bit						5
#define PLLCFG_PSEL0_bit					5
#define PLLCFG_PSEL1_bit					6

#define PLLCFG_MSEL0						(1 << PLLCFG_MSEL0_bit)
#define PLLCFG_MSEL1						(1 << PLLCFG_MSEL1_bit)
#define PLLCFG_MSEL2						(1 << PLLCFG_MSEL2_bit)
#define PLLCFG_MSEL3						(1 << PLLCFG_MSEL3_bit)
#define PLLCFG_MSEL4						(1 << PLLCFG_MSEL4_bit)
#define PLLCFG_PSEL0						(1 << PLLCFG_PSEL0_bit)
#define PLLCFG_PSEL1						(1 << PLLCFG_PSEL1_bit)

#define PLLCFG_MSEL_1_value					0
#define PLLCFG_MSEL_2_value					1
#define PLLCFG_MSEL_3_value					2
#define PLLCFG_MSEL_4_value					3
#define PLLCFG_MSEL_5_value					4
#define PLLCFG_MSEL_6_value					5
#define PLLCFG_MSEL_7_value					6
#define PLLCFG_MSEL_8_value					7
#define PLLCFG_MSEL_9_value					8
#define PLLCFG_MSEL_10_value				9
#define PLLCFG_MSEL_11_value				10
#define PLLCFG_MSEL_12_value				11
#define PLLCFG_MSEL_13_value				12
#define PLLCFG_MSEL_14_value				13
#define PLLCFG_MSEL_15_value				14
#define PLLCFG_MSEL_16_value				15
#define PLLCFG_MSEL_17_value				16
#define PLLCFG_MSEL_18_value				17
#define PLLCFG_MSEL_19_value				18
#define PLLCFG_MSEL_20_value				19
#define PLLCFG_MSEL_21_value				20
#define PLLCFG_MSEL_22_value				21
#define PLLCFG_MSEL_23_value				22
#define PLLCFG_MSEL_24_value				23
#define PLLCFG_MSEL_25_value				24
#define PLLCFG_MSEL_26_value				25
#define PLLCFG_MSEL_27_value				26
#define PLLCFG_MSEL_28_value				27
#define PLLCFG_MSEL_29_value				28
#define PLLCFG_MSEL_30_value				29
#define PLLCFG_MSEL_31_value				30
#define PLLCFG_MSEL_32_value				31
#define PLLCFG_MSEL_mask					31

#define PLLCFG_PSEL_1_value					0
#define PLLCFG_PSEL_2_value					1
#define PLLCFG_PSEL_4_value					2
#define PLLCFG_PSEL_8_value					3
#define PLLCFG_PSEL_mask					3

#define PLLCFG_MSEL_1						(PLLCFG_MSEL_1_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_2						(PLLCFG_MSEL_2_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_3						(PLLCFG_MSEL_3_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_4						(PLLCFG_MSEL_4_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_5						(PLLCFG_MSEL_5_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_6						(PLLCFG_MSEL_6_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_7						(PLLCFG_MSEL_7_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_8						(PLLCFG_MSEL_8_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_9						(PLLCFG_MSEL_9_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_10						(PLLCFG_MSEL_10_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_11						(PLLCFG_MSEL_11_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_12						(PLLCFG_MSEL_12_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_13						(PLLCFG_MSEL_13_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_14						(PLLCFG_MSEL_14_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_15						(PLLCFG_MSEL_15_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_16						(PLLCFG_MSEL_16_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_17						(PLLCFG_MSEL_17_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_18						(PLLCFG_MSEL_18_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_19						(PLLCFG_MSEL_19_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_20						(PLLCFG_MSEL_20_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_21						(PLLCFG_MSEL_21_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_22						(PLLCFG_MSEL_22_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_23						(PLLCFG_MSEL_23_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_24						(PLLCFG_MSEL_24_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_25						(PLLCFG_MSEL_25_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_26						(PLLCFG_MSEL_26_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_27						(PLLCFG_MSEL_27_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_28						(PLLCFG_MSEL_28_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_29						(PLLCFG_MSEL_29_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_30						(PLLCFG_MSEL_30_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_31						(PLLCFG_MSEL_31_value << PLLCFG_MSEL_bit)
#define PLLCFG_MSEL_32						(PLLCFG_MSEL_32_value << PLLCFG_MSEL_bit)

#define PLLCFG_PSEL_1						(PLLCFG_PSEL_1_value << PLLCFG_PSEL_bit)
#define PLLCFG_PSEL_2						(PLLCFG_PSEL_2_value << PLLCFG_PSEL_bit)
#define PLLCFG_PSEL_4						(PLLCFG_PSEL_4_value << PLLCFG_PSEL_bit)
#define PLLCFG_PSEL_8						(PLLCFG_PSEL_8_value << PLLCFG_PSEL_bit)

/*
+-----------------------------------------------------------------------------+
| PLLSTAT - PLL Status register
+-----------------------------------------------------------------------------+
*/

#define PLLSTAT_MSEL_bit					0
#define PLLSTAT_MSEL0_bit					0
#define PLLSTAT_MSEL1_bit					1
#define PLLSTAT_MSEL2_bit					2
#define PLLSTAT_MSEL3_bit					3
#define PLLSTAT_MSEL4_bit					4
#define PLLSTAT_PSEL_bit					5
#define PLLSTAT_PSEL0_bit					5
#define PLLSTAT_PSEL1_bit					6
#define PLLSTAT_PLLE_bit					8
#define PLLSTAT_PLLC_bit					9
#define PLLSTAT_PLOCK_bit					10

#define PLLSTAT_MSEL0						(1 << PLLSTAT_MSEL0_bit)
#define PLLSTAT_MSEL1						(1 << PLLSTAT_MSEL1_bit)
#define PLLSTAT_MSEL2						(1 << PLLSTAT_MSEL2_bit)
#define PLLSTAT_MSEL3						(1 << PLLSTAT_MSEL3_bit)
#define PLLSTAT_MSEL4						(1 << PLLSTAT_MSEL4_bit)
#define PLLSTAT_PSEL0						(1 << PLLSTAT_PSEL0_bit)
#define PLLSTAT_PSEL1						(1 << PLLSTAT_PSEL1_bit)
#define PLLSTAT_PLLE						(1 << PLLSTAT_PLLE_bit)
#define PLLSTAT_PLLC						(1 << PLLSTAT_PLLC_bit)
#define PLLSTAT_PLOCK						(1 << PLLSTAT_PLOCK_bit)

#define PLLSTAT_MSEL_1_value				0
#define PLLSTAT_MSEL_2_value				1
#define PLLSTAT_MSEL_3_value				2
#define PLLSTAT_MSEL_4_value				3
#define PLLSTAT_MSEL_5_value				4
#define PLLSTAT_MSEL_6_value				5
#define PLLSTAT_MSEL_7_value				6
#define PLLSTAT_MSEL_8_value				7
#define PLLSTAT_MSEL_9_value				8
#define PLLSTAT_MSEL_10_value				9
#define PLLSTAT_MSEL_11_value				10
#define PLLSTAT_MSEL_12_value				11
#define PLLSTAT_MSEL_13_value				12
#define PLLSTAT_MSEL_14_value				13
#define PLLSTAT_MSEL_15_value				14
#define PLLSTAT_MSEL_16_value				15
#define PLLSTAT_MSEL_17_value				16
#define PLLSTAT_MSEL_18_value				17
#define PLLSTAT_MSEL_19_value				18
#define PLLSTAT_MSEL_20_value				19
#define PLLSTAT_MSEL_21_value				20
#define PLLSTAT_MSEL_22_value				21
#define PLLSTAT_MSEL_23_value				22
#define PLLSTAT_MSEL_24_value				23
#define PLLSTAT_MSEL_25_value				24
#define PLLSTAT_MSEL_26_value				25
#define PLLSTAT_MSEL_27_value				26
#define PLLSTAT_MSEL_28_value				27
#define PLLSTAT_MSEL_29_value				28
#define PLLSTAT_MSEL_30_value				29
#define PLLSTAT_MSEL_31_value				30
#define PLLSTAT_MSEL_32_value				31
#define PLLSTAT_MSEL_mask					31

#define PLLSTAT_PSEL_1_value				0
#define PLLSTAT_PSEL_2_value				1
#define PLLSTAT_PSEL_4_value				2
#define PLLSTAT_PSEL_8_value				3
#define PLLSTAT_PSEL_mask					3

#define PLLSTAT_MSEL_1						(PLLSTAT_MSEL_1_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_2						(PLLSTAT_MSEL_2_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_3						(PLLSTAT_MSEL_3_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_4						(PLLSTAT_MSEL_4_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_5						(PLLSTAT_MSEL_5_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_6						(PLLSTAT_MSEL_6_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_7						(PLLSTAT_MSEL_7_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_8						(PLLSTAT_MSEL_8_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_9						(PLLSTAT_MSEL_9_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_10						(PLLSTAT_MSEL_10_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_11						(PLLSTAT_MSEL_11_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_12						(PLLSTAT_MSEL_12_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_13						(PLLSTAT_MSEL_13_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_14						(PLLSTAT_MSEL_14_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_15						(PLLSTAT_MSEL_15_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_16						(PLLSTAT_MSEL_16_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_17						(PLLSTAT_MSEL_17_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_18						(PLLSTAT_MSEL_18_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_19						(PLLSTAT_MSEL_19_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_20						(PLLSTAT_MSEL_20_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_21						(PLLSTAT_MSEL_21_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_22						(PLLSTAT_MSEL_22_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_23						(PLLSTAT_MSEL_23_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_24						(PLLSTAT_MSEL_24_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_25						(PLLSTAT_MSEL_25_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_26						(PLLSTAT_MSEL_26_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_27						(PLLSTAT_MSEL_27_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_28						(PLLSTAT_MSEL_28_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_29						(PLLSTAT_MSEL_29_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_30						(PLLSTAT_MSEL_30_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_31						(PLLSTAT_MSEL_31_value << PLLSTAT_MSEL_bit)
#define PLLSTAT_MSEL_32						(PLLSTAT_MSEL_32_value << PLLSTAT_MSEL_bit)

#define PLLSTAT_PSEL_1						(PLLSTAT_PSEL_1_value << PLLSTAT_PSEL_bit)
#define PLLSTAT_PSEL_2						(PLLSTAT_PSEL_2_value << PLLSTAT_PSEL_bit)
#define PLLSTAT_PSEL_4						(PLLSTAT_PSEL_4_value << PLLSTAT_PSEL_bit)
#define PLLSTAT_PSEL_8						(PLLSTAT_PSEL_8_value << PLLSTAT_PSEL_bit)

/*
+-----------------------------------------------------------------------------+
| PLLFEED - PLL Feed register
+-----------------------------------------------------------------------------+
*/

#define PLLFEED_FIRST						0xAA
#define PLLFEED_SECOND						0x55

/*
+-----------------------------------------------------------------------------+
| PCON - Power Control register
+-----------------------------------------------------------------------------+
*/

#define PCON_IDL_bit						0
#define PCON_PD_bit							1

#define PCON_IDL							(1 << PCON_IDL_bit)
#define PCON_PD								(1 << PCON_PD_bit)

/*
+-----------------------------------------------------------------------------+
| PCONP - Power Control for Peripherals register
+-----------------------------------------------------------------------------+
*/

#define PCONP_PCTIM0_bit					1
#define PCONP_PCTIM1_bit					2
#define PCONP_PCUART0_bit					3
#define PCONP_PCUART1_bit					4
#define PCONP_PCI2C0_bit					7
#define PCONP_PCSPI_bit						8
#define PCONP_PCRTC_bit						9
#define PCONP_PCSSP_bit						10
#define PCONP_PCAD_bit						12
#define PCONP_PCI2C1_bit					19
#define PCONP_PCTIM2_bit					28
#define PCONP_PCTIM3_bit					29

#define PCONP_PCTIM0						(1 << PCONP_PCTIM0_bit)
#define PCONP_PCTIM1						(1 << PCONP_PCTIM1_bit)
#define PCONP_PCUART0						(1 << PCONP_PCUART0_bit)
#define PCONP_PCUART1						(1 << PCONP_PCUART1_bit)
#define PCONP_PCI2C0						(1 << PCONP_PCI2C0_bit)
#define PCONP_PCSPI							(1 << PCONP_PCSPI_bit)
#define PCONP_PCRTC							(1 << PCONP_PCRTC_bit)
#define PCONP_PCSSP							(1 << PCONP_PCSSP_bit)
#define PCONP_PCAD							(1 << PCONP_PCAD_bit)
#define PCONP_PCI2C1						(1 << PCONP_PCI2C1_bit)
#define PCONP_PCTIM2						(1 << PCONP_PCTIM2_bit)
#define PCONP_PCTIM3						(1 << PCONP_PCTIM3_bit)

/*
+-----------------------------------------------------------------------------+
| RSIR - Reset Source Identification Register
+-----------------------------------------------------------------------------+
*/

#define RSIR_POR_bit						0
#define RSIR_EXTR_bit						1
#define RSIR_WDTR_bit						2

#define RSIR_POR							(1 << RSIR_POR_bit)
#define RSIR_EXTR							(1 << RSIR_EXTR_bit)
#define RSIR_WDTR							(1 << RSIR_WDTR_bit)

/*
+-----------------------------------------------------------------------------+
| APBDIV - APB Divider register
+-----------------------------------------------------------------------------+
*/

#define APBDIV_APBDIV_bit					0
#define APBDIV_APBDIV0_bit					0
#define APBDIV_APBDIV1_bit					1

#define APBDIV_APBDIV						(1 << APBDIV_APBDIV_bit)
#define APBDIV_APBDIV0						(1 << APBDIV_APBDIV0_bit)
#define APBDIV_APBDIV1						(1 << APBDIV_APBDIV1_bit)

#define APBDIV_APBDIV_4_value				0
#define APBDIV_APBDIV_1_value				1
#define APBDIV_APBDIV_2_value				2
#define APBDIV_APBDIV_mask					3

#define APBDIV_APBDIV_4						(APBDIV_APBDIV_4_value << APBDIV_APBDIV_bit)
#define APBDIV_APBDIV_1						(APBDIV_APBDIV_1_value << APBDIV_APBDIV_bit)
#define APBDIV_APBDIV_2						(APBDIV_APBDIV_2_value << APBDIV_APBDIV_bit)

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* HDR_SCB_H_ */

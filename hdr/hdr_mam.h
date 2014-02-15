/** \file hdr_mam.h
 * \brief Header with definition of bits in MAM control registers
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* chip: LPC2xxx
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/

#ifndef HDR_MAM_H_
#define HDR_MAM_H_

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

/*
+-----------------------------------------------------------------------------+
| MAMCR - MAM Control register
+-----------------------------------------------------------------------------+
*/

#define MAMCR_MODE_bit					0
#define MAMCR_MODE0_bit					0
#define MAMCR_MODE1_bit					1

#define MAMCR_MODE0						(1 << MAMCR_MODE0_bit)
#define MAMCR_MODE1						(1 << MAMCR_MODE1_bit)

#define MAMCR_MODE_DISABLED_value		0
#define MAMCR_MODE_PARTIAL_value		1
#define MAMCR_MODE_FULL_value			2
#define MAMCR_MODE_mask					3

#define MAMCR_MODE_DISABLED				(MAMCR_MODE_DISABLED_value << MAMCR_MODE_bit)
#define MAMCR_MODE_PARTIAL				(MAMCR_MODE_PARTIAL_value << MAMCR_MODE_bit)
#define MAMCR_MODE_FULL					(MAMCR_MODE_FULL_value << MAMCR_MODE_bit)

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* HDR_MAM_H_ */

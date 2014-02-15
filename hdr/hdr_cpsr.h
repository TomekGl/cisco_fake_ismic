/** \file hdr_cpsr.h
 * \brief Header with definition of bits in CPSR register
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* chip: ARMv4 (ARM7TDMI)
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/

#ifndef HDR_CPSR_H_
#define HDR_CPSR_H_

/*
+=============================================================================+
| global definitions
+=============================================================================+
*/

/*
+-----------------------------------------------------------------------------+
| mode bits
+-----------------------------------------------------------------------------+
*/

#define USER_MODE			0b10000			// User mode
#define FIQ_MODE			0b10001			// FIQ mode
#define IRQ_MODE			0b10010			// IRQ mode
#define SUPERVISOR_MODE		0b10011			// Supervisor mode
#define ABORT_MODE			0b10111			// Abort mode
#define UNDEFINED_MODE		0b11011			// Undefined mode
#define SYSTEM_MODE			0b11111			// System mode

/*
+-----------------------------------------------------------------------------+
| interrupt disable bits
+-----------------------------------------------------------------------------+
*/

#define CPSR_I_bit			7
#define CPSR_F_bit			6

#define CPSR_I				(1 << CPSR_I_bit)	// clear - IRQs enabled, set - disabled
#define CPSR_F				(1 << CPSR_F_bit)	// clear - FIQs enabled, set - disabled

/******************************************************************************
* END OF FILE
******************************************************************************/
#endif /* HDR_CPSR_H_ */

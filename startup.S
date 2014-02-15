/******************************************************************************
* author: Freddie Chopin, http://www.freddiechopin.info/
* file: startup.S
* last change: 2012-01-08
*
* chip: ARMv4 (ARM7TDMI)
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
*
* description:
* ARMv4 (ARM7TDMI) assembly startup code
******************************************************************************/

/*
+=============================================================================+
| includes
+=============================================================================+
*/

#include "hdr/hdr_cpsr.h"

/*
+=============================================================================+
| ARMv4 (ARM7TDMI) startup code
+=============================================================================+
*/

.text
.balign 2
.syntax unified
.arm
.func   Reset_Handler
.global Reset_Handler

Reset_Handler:

/*
+-----------------------------------------------------------------------------+
| Stack setup
+-----------------------------------------------------------------------------+
*/

	// after reset the core is in Supervisor mode with IRQ & FIQ disabled
	ldr   sp, =__supervisor_stack_end;				// set the stack for Supervisor mode
	msr   CPSR_c, #FIQ_MODE | CPSR_I | CPSR_F		// switch to FIQ mode, IRQ & FIQ disabled
	ldr   sp, =__fiq_stack_end;						// set the stack for FIQ mode
	msr   CPSR_c, #IRQ_MODE | CPSR_I | CPSR_F 		// switch to IRQ mode, IRQ & FIQ disabled
	ldr   sp, =__irq_stack_end;						// set the stack for IRQ mode
	msr   CPSR_c, #ABORT_MODE | CPSR_I | CPSR_F		// switch to Abort mode, IRQ & FIQ disabled
	ldr   sp, =__abort_stack_end;					// set the stack for Abort mode
	msr   CPSR_c, #UNDEFINED_MODE | CPSR_I | CPSR_F	// switch to Undefined mode, IRQ & FIQ disabled
	ldr   sp, =__undefined_stack_end;				// set the stack for Undefined mode
	msr   CPSR_c, #SYSTEM_MODE					 	// switch to System mode, IRQ & FIQ enabled
	ldr   sp, =__user_system_stack_end;				// set the stack for User and System mode

/*
+-----------------------------------------------------------------------------+
| Branch to low_level_init_0() function (.data and .bss are not initialized!)
+-----------------------------------------------------------------------------+
*/

	ldr		r0, =low_level_init_0
	mov		lr, pc
	bx		r0

/*
+-----------------------------------------------------------------------------+
| Initialize .data section
+-----------------------------------------------------------------------------+
*/

	ldr     r1, =__data_init_start
	ldr     r2, =__data_start
	ldr     r3, =__data_end
1:	cmp     r2, r3
	ldrlo   r0, [r1], #4
	strlo   r0, [r2], #4
	blo     1b

/*
+-----------------------------------------------------------------------------+
| Zero-init .bss section
+-----------------------------------------------------------------------------+
*/

	mov     r0, #0
	ldr     r1, =__bss_start
	ldr     r2, =__bss_end
1:	cmp     r1, r2
	strlo   r0, [r1], #4
	blo     1b

/*
+-----------------------------------------------------------------------------+
| Call C++ constructors for global and static objects
+-----------------------------------------------------------------------------+
*/
#ifdef __USES_CXX
	ldr		r0, =__libc_init_array
	mov		lr, pc
	bx		r0
#endif

/*
+-----------------------------------------------------------------------------+
| Branch to low_level_init_1() function
+-----------------------------------------------------------------------------+
*/

	ldr		r0, =low_level_init_1
	mov		lr, pc
	bx		r0

/*
+-----------------------------------------------------------------------------+
| Branch to main() with link
+-----------------------------------------------------------------------------+
*/

	ldr		r0, =main
	mov		lr, pc
	bx		r0

/*
+-----------------------------------------------------------------------------+
| Call C++ destructors for global and static objects
+-----------------------------------------------------------------------------+
*/
#ifdef __USES_CXX
	ldr		r0, =__libc_fini_array
	mov		lr, pc
	bx		r0
#endif

/*
+-----------------------------------------------------------------------------+
| On return - loop till the end of the world
+-----------------------------------------------------------------------------+
*/

	b		.

.endfunc

/*
+=============================================================================+
| __default_low_level_init() - replacement for undefined low_level_init_0()
| and/or low_level_init_1(). This function just returns.
+=============================================================================+
*/

.text
.balign 2
.syntax unified
.arm
.func   __default_low_level_init
.global __default_low_level_init

__default_low_level_init:
	bx		lr

.endfunc

/*
+=============================================================================+
| assign undefined low_level_init_0() and/or low_level_init_1() to
| __default_low_level_init()
+=============================================================================+
*/

.weak	low_level_init_0
.global	low_level_init_0
.set	low_level_init_0, __default_low_level_init

.weak	low_level_init_1
.global	low_level_init_1
.set	low_level_init_1, __default_low_level_init

/******************************************************************************
* END OF FILE
******************************************************************************/

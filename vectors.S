/******************************************************************************
* author: Freddie Chopin, http://www.freddiechopin.info/
* file: vectors.S
* last change: 2012-01-08
*
* chip: LPC2xxx
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
*
* description:
* LPC2xxx vector table and __Default_Handler()
******************************************************************************/

/*
+=============================================================================+
| Default interrupt handler, used for interrupts that don't have their own
| handler defined. On ARMv4 architecture it cannot return, as each interrupt
| has its own return method!
+=============================================================================+
*/

.text
.balign 2
.syntax unified
.arm
.func __Default_Handler
.global __Default_Handler

__Default_Handler:
	b .

.endfunc

/*
+=============================================================================+
| assign all unhandled interrupts to the default handler
+=============================================================================+
*/

// Undefined instruction
.weak	Undefined_Handler
.global	Undefined_Handler
.set	Undefined_Handler, __Default_Handler

// Software interrupt (SWI)
.weak	SWI_Handler
.global	SWI_Handler
.set	SWI_Handler, __Default_Handler

// Prefetch Abort (instruction fetch memory abort)
.weak	Prefetch_Abort_Handler
.global	Prefetch_Abort_Handler
.set	Prefetch_Abort_Handler, __Default_Handler

// Data Abort (data access memory abort)
.weak	Data_Abort_Handler
.global	Data_Abort_Handler
.set	Data_Abort_Handler, __Default_Handler

// FIQ (fast interrupt)
.weak	FIQ_Handler
.global	FIQ_Handler
.set	FIQ_Handler, __Default_Handler

/*
+=============================================================================+
| Vector table
+=============================================================================+
*/

// VIC IRQ vector for older LPCs (where &VICVectAddr = 0xFFFFF030, e.g. LPC2103):
//		ldr		pc, [pc, #-0xFF0]
// VIC IRQ vector for newer LPCs (where &VICAddress = 0xFFFFFF00, e.g. LPC2478):
//		ldr		pc, [pc, #-0x120]

.section .vectors
.balign 2
.syntax unified
.arm
__vectors:

	ldr		pc, =Reset_Handler				// Reset exception
	ldr		pc, =Undefined_Handler			// Undefined Instruction exception
	ldr		pc, =SWI_Handler				// Software Interrupt exception
	ldr		pc, =Prefetch_Abort_Handler		// Prefetch Abort exception
	ldr		pc, =Data_Abort_Handler			// Data Abort exception
	nop										// reserved for code signature
	ldr		pc, [pc, #-0xFF0]				// Interrupt exception -> VIC
	ldr		pc, =FIQ_Handler				// Fast Interrupt exception

/******************************************************************************
* END OF FILE
******************************************************************************/

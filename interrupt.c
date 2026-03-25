#include <lpc21xx.h>          // LPC21xx register definitions
#include "interrupt.h"        // Header file for interrupt functions
#include "interrupt_defines.h"// Macro definitions for interrupts
#include "types.h"            // Custom data types

// Global flag to indicate setup interrupt occurred
volatile s32 setup_flag = 0;

// Global flag to indicate acknowledgment interrupt occurred
volatile s32 ack_flag = 0;

// ISR for External Interrupt 0
void EINT0_ISR(void) __irq
{
	setup_flag = 1;        // Set flag when interrupt occurs

	EXTINT = 1 << 0;       // Clear EINT0 interrupt flag

	VICVectAddr = 0;       // Acknowledge interrupt to VIC
}

// ISR for External Interrupt 1
void EINT1_ISR(void) __irq
{
	ack_flag = 1;          // Set acknowledgment flag

	EXTINT = 1 << 1;       // Clear EINT1 interrupt flag

	VICVectAddr = 0;       // Acknowledge interrupt to VIC
}

// Function to initialize interrupts
void interrupt_init()
{
    // Configure P0.1 and P0.3 as EINT0 and EINT1 pins

	// Clear bits 2,3 and 6,7 (for P0.1 and P0.3)
	PINSEL0 &= ((u32)~3 << 2) | ((u32)~3 << 6);

	// Set pin functions for EINT0 and EINT1
	PINSEL0 |= EINT0_INPUT_PIN | EINT1_INPUT_PIN;

	// Enable EINT0 and EINT1 interrupts in VIC
	VICIntEnable = (1 << EINT0_VIC_CHNO) | (1 << EINT1_VIC_CHNO);

	// Configure EINT0 as vectored IRQ with highest priority
	VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO;

	// Assign ISR address to vector slot 0
	VICVectAddr0 = (u32)EINT0_ISR;

	// Configure EINT1 as vectored IRQ with next priority
	VICVectCntl1 = (1 << 5) | EINT1_VIC_CHNO;

	// Assign ISR address to vector slot 1
	VICVectAddr1 = (u32)EINT1_ISR;

	// Configure EINT0 and EINT1 as edge-triggered interrupts
	EXTMODE = (1 << 1) | (1 << 0);

	// Configure as falling-edge triggered (default EXTPOLAR = 0)

	// Configure LED pin as output (status indication)
	IODIR1 |= (1 << EINT0_STATUS_LED);
}

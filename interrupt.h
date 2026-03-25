#ifndef INTERRUPT_H   // Prevent multiple inclusion
#define INTERRUPT_H

// Function declaration for interrupt initialization
void interrupt_init(void);

// External flag to indicate EINT0 event
extern volatile int setup_flag;

// External flag to indicate EINT1 event
extern volatile int ack_flag;

#endif

//delay.c
//delay.c

#include "types.h"   // Include custom type definitions (like u32)

// Function to generate delay in microseconds
void delay_us(u32 dlyus)
{
	// Multiply delay value to approximate microsecond delay
	for(dlyus *= 12; dlyus > 0; dlyus--);  // Empty loop for delay
}

// Function to generate delay in milliseconds
void delay_ms(u32 dlyms)
{
	// Multiply delay value to approximate millisecond delay
	for(dlyms *= 12000; dlyms > 0; dlyms--);  // Empty loop for delay
}

// Function to generate delay in seconds
void delay_s(u32 dlys)
{
	// Multiply delay value to approximate second delay
	for(dlys *= 12000000; dlys > 0; dlys--);  // Empty loop for delay
}

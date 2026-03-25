#include "types.h"  
// Includes custom data types like s32 (signed 32-bit), u8, etc.
s32 read_two_digit(void);  
// Function to read a 2-digit number from keypad (00–99)
s32 read_four_digit(void);  
// Function to read a 4-digit number (typically used for year input)
s32 read_single_digit(void);  
// Function to read a single digit (0–9) from keypad
void configure_medicine(void);  
// Function to configure medicine schedule (hour & minute for each medicine)
void alert_user(void);  
// Function to alert user using buzzer and LCD when it's time for medicine
void check_medicine_time(s32,s32);  
// Function to compare current time (hour, minute) with stored medicine times
// and trigger alert if matched

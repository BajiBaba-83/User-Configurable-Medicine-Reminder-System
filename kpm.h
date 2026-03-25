//kpm.h

#include "types.h"        // Include user-defined data types like u8, u32

void InitKPM(void);      // Function to initialize keypad
u32 ColScan(void);       // Function to scan columns
u32 RowCheck(void);      // Function to detect which row is active
u32 ColCheck(void);      // Function to detect which column is active
u8 KeyScan(void);        // Function to scan and return pressed key
u32 ReadNum(void);       // Function to read numeric input from keypad

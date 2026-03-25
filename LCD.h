#include "types.h"        // Include custom data types

void WriteLCD(u8 data);   // Write raw data/command to LCD
void CmdLCD(u8 cmd);      // Send command to LCD
void CharLCD(u8 ascii);   // Send single character to LCD
void InitLCD(void);       // Initialize LCD
void StrLCD(s8* p);       // Display string
void U32LCD(u32 n);       // Display unsigned integer
void S32LCD(s32 n);       // Display signed integer
void F32LCD(f32 fnum, u8 nDP); // Display float with decimal points
void HEXLCD(u32 n);       // Display hexadecimal value
void BinLCD(u32 n, u8 nbd); // Display binary value
void BuildCGRAM(u8* p, u8 nb); // Create custom characters

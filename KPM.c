#include "types.h"         // Custom type definitions (u8, u32)
#include "defines.h"       // General macros (like WNIBBLE, RNIBBLE, RBIT)
#include <lpc21xx.h>      // LPC21xx register definitions
#include "kpm_defines.h"   // Keypad pin definitions
#include "lcd.h"           // LCD functions (CharLCD etc.)
u8 kpmLUT[4][4]={{'7','8','9','/'},   // Row 0 keys
                 {'4','5','6','*'},   // Row 1 keys
                 {'1','2','3','-'},   // Row 2 keys
                 {'C','0','=','+'}};  // Row 3 keys

void InitKPM(void)
{
    WNIBBLE(IODIR1,ROW0,15);  
    // Set P1.16 to P1.19 (rows) as output (1111 = 15)
}

u32 ColScan(void)
{
    return((RNIBBLE(IOPIN1,COL0)<15)?0:1);
    // Read columns (P1.20–P1.23)
    // If any column is LOW (key pressed), return 0
    // If all HIGH (no key), return 1
}
u32 RowCheck(void)
{
    u32 rno;   // Variable to store row number

    for(rno=0; rno<4; rno++)   // Loop through 4 rows
    {
        WNIBBLE(IOPIN1,ROW0,~(1<<rno));  
        // Make one row LOW at a time

        if(ColScan()==0)   // If key detected
        {
            break;         // Exit loop (row found)
        }
    }

    // Reset rows to default state (all HIGH)
    WNIBBLE(IOPIN1,ROW0,0x0);
    return rno;   // Return detected row number
}

u32 ColCheck(void)
{
    u32 cno;   // Variable to store column number

    for(cno=0; cno<4; cno++)   // Loop through columns
    {
        if(RBIT(IOPIN1,(COL0+cno))==0)  
        // Check if column pin is LOW (pressed)
        {
            break;   // Column found
        }
    }
    return cno;   // Return column number
}

u8 KeyScan(void)
{
    u32 rno,cno,keyv;   // Variables for row, column, key value

    while(ColScan());  
    // Wait until any key is pressed

    rno=RowCheck();  
    // Identify row number

    cno=ColCheck();  
    // Identify column number

    keyv=kpmLUT[rno][cno];  
    // Get corresponding key from lookup table

    while(!ColScan());  
    // Wait until key is released (debounce)

    return keyv;  
    // Return pressed key
}

u32 ReadNum(void)
{
    u8 key;          // Store pressed key
    u32 sum=0;       // Store final number

    while(1)         // Infinite loop
    {
        key=KeyScan();   // Get key input

        if(key>='0'&&key<='9')   // Check if numeric key
        {
            CharLCD(key);   // Display key on LCD

            sum=(sum*10)+(key-'0');  
            // Convert ASCII to integer and accumulate

            break;   // Exit after one digit (NOTE: only single digit read)
        }
    }
    return sum;   // Return the number
}

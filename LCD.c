#include<lpc21xx.h>        // LPC21xx registers
#include "LCD_defines.h"   // LCD pin definitions
#include "types.h"         // Data types
#include "defines.h"       // Bit manipulation macros
#include "delay.h"         // Delay functions

void WriteLCD(u8 data)
{
    SCLRBIT(IOCLR0,RW);    // RW=0  Write operation
    WBYTE(IOPIN0,LCD_DATA,data); // Send 8-bit data to LCD pins

    SSETBIT(IOSET0,EN);    // EN=1  Enable high
    delay_us(1);           // Small delay
    SCLRBIT(IOCLR0,EN);    // EN=0  Falling edge triggers LCD
    delay_ms(2);           // Wait for LCD to process
}

void CmdLCD(u8 cmd)
{
    SCLRBIT(IOCLR0,RS);    // RS=0  Command register
    WriteLCD(cmd);         // Send command
}

void CharLCD(u8 ascii)
{
    SSETBIT(IOSET0,RS);    // RS=1  Data register
    WriteLCD(ascii);       // Send character
}

void InitLCD(void)
{
  WBYTE(IODIR0,LCD_DATA,255); // Set P0.8–P0.15 as output
  SETBIT(IODIR0,RS);          // RS as output
  SETBIT(IODIR0,RW);          // RW as output
  SETBIT(IODIR0,EN);          // EN as output
	
	delay_ms(15);								// LCD power-up delay
	
	CmdLCD(MODE_8BIT_1LINE);    // Initialize sequence
  delay_ms(5);
  CmdLCD(MODE_8BIT_1LINE);
  delay_us(100);
  CmdLCD(MODE_8BIT_1LINE);
	
	CmdLCD(MODE_8BIT_2LINE);    // Set 2-line mode
  CmdLCD(DISP_ON);            // Turn display ON
  CmdLCD(CLEAR_LCD);          // Clear display
  CmdLCD(SHIFT_CUR_RIGHT);    // Cursor move direction
}

void StrLCD(s8* p)
{
	while(*p) 									// Loop until Null Character
	CharLCD(*p++);							// Print Each Character
}

void U32LCD(u32 n)
{
    u8 a[10];       // Array to store digits
    s32 i=0;

    if(n==0)
    {
        CharLCD('0');   // Handle zero case
    }
    else
    {
        while(n)
        {
            a[i++]=(n%10)+48; // Convert digit to ASCII
            n/=10;            // Remove last digit
        }
        for(--i;i>=0;i--)
            CharLCD(a[i]);    // Print digits in reverse
    }
}

void S32LCD(s32 n)
{
    if(n<0)
    {
        CharLCD('-');   // Print negative sign
        n=-n;
        U32LCD(n);      // Print absolute value
    }
}

void F32LCD(f32 fnum, u8 nDP)
{
    u32 n;
    s32 i;

    if(fnum<0)
    {
        CharLCD('-');   // Negative sign
    }

    n=fnum;             // Integer part
    U32LCD(n);
    CharLCD('.');       // Decimal point
	  for(i=0; i<nDP; i++)
    {
        fnum=(fnum-n)*10;  // Extract decimal digits
        n=fnum;
        CharLCD(n+48);     // Print digit
    }
}

void HEXLCD(u32 n)
{
	u8 a[8],rem;
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n)
		{
			rem =n%16;
			(rem<10)?(rem+=48):(rem+=55);//Convert to Ascii
			a[i++]=rem;
			n/=16;
		}
		for(--i; i>=0; i--)
		{
			CharLCD(a[i]);							// Print HEX digits
		}
	}
}

void BinLCD(u32 n, u8 nbd)
{
	s32 i;
	for(i=(nbd-1); i>=0; i--)
	{
		CharLCD(((n>>i)&1)+48);				// Extract Each bit
	}
}
void BuildCGRAM(u8* p, u8 nb)
{
	s32 i;
	CmdLCD(GOTO_CGRAM);							// Go to CGRAM
	for(i=0; i<=nb; i++)
	{
		CharLCD(p[i]);								// Write Pattern Data 
	}
	CmdLCD(GOTO_LINE1_POS0);        // Return to DDRAM
}


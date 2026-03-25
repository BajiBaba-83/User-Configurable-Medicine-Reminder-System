//rtc_edit.c

#include <lpc21xx.h>        // LPC21xx register definitions
#include "lcd.h"            // LCD functions
#include "kpm.h"            // Keypad functions
#include "medicine.h"       // (Used for input functions like read_two_digit)
#include "rtc_defines.h"    // RTC register macros (HOUR, MIN, etc.)
#include "rtc_edit.h"       // Function declaration
#include "LCD_defines.h"    // LCD command macros
#include "delay.h"          // Delay functions

void edit_rtc_time()
{
    s32 hh,mm,ss,d,m,y,dow;  
    // Variables for hour, minute, second, date, month, year, day

    u8 key;  														// Variable to store keypad input
    CmdLCD(CLEAR_LCD);              		// Clear LCD screen
    StrLCD("Edit Time");  							// Display title
    delay_ms(100);  										// Small delay
    CCR = RTC_RESET;      							// Stop RTC before modifying values

    CmdLCD(GOTO_LINE1_POS0);						// Ask user whether to edit hour or skip
		StrLCD("'='hour '-'skip");
		key=KeyScan();											// Read key input
		if(key=='-')
		{
				goto min;												// Skip hour editing
		}
		else if(key=='=')
		{
		hour:CmdLCD(CLEAR_LCD);							// Label for retry if invalid input
    StrLCD("Hour:(00-23)");							// Prompt user
		CmdLCD(GOTO_LINE2_POS0);
    hh = read_two_digit();							// Read 2-digit hour
		if(hh<0 || hh>23)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid hour!");
			delay_ms(100);
			goto hour;												// Retry
		}
		HOUR = hh;													// Write to RTC register
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto min;													// Go to minute
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;									// Restart RTC
			return;														// Exit
		}
	}
			
	min:CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("'='min '-'skip");
		key=KeyScan();
		if(key=='-')
		{
				goto sec;												// Skip minute
		}
		else if(key == '=')
		{
		min1:CmdLCD(CLEAR_LCD);
    StrLCD("Minute:(00-59)");
		CmdLCD(GOTO_LINE2_POS0);
    mm = read_two_digit();
		if(mm<0 || mm>59)
		{
			CmdLCD(CLEAR_LCD);								
			StrLCD("Invalid Minute!");
			delay_ms(100);
			goto min1;
		}
		MIN=mm;															// Set minute
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto sec;													// Goto Sec
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
	}
		
	sec:CmdLCD(CLEAR_LCD);
		StrLCD("'='sec '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto D;													// Skip seconds
		}
		else if(key=='=')
		{
		sec1:CmdLCD(CLEAR_LCD);
    StrLCD("Second:(00-59)");
    CmdLCD(GOTO_LINE2_POS0);
		ss = read_two_digit();
		if(ss<0 || ss>59)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid second!");
			delay_ms(100);
			goto sec1;
		}
		SEC=ss;															// Set seconds
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto D;														// Go to Data
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
	}
		
	D:CmdLCD(CLEAR_LCD);
		StrLCD("'='date '-'skip");
	  key=KeyScan();
		if(key=='-')
		{
				goto M;														//Skip Date
		}
		else if(key=='=')
		{
		D1:CmdLCD(CLEAR_LCD);
			StrLCD("Edit Date");
			delay_ms(100);
			CmdLCD(CLEAR_LCD);
		StrLCD("Date:(01-31)");
		CmdLCD(GOTO_LINE2_POS0);
		d=read_two_digit();
		if(d<1 || d>31)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid date!");
			delay_ms(100);
			goto D1;
		}
		DOM=d;																// Set date
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto M;															// Go to Month
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
	}
		
	M:CmdLCD(CLEAR_LCD);
		StrLCD("'='month '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto Y;														//Skip Month
		}
		else if(key=='=')
		{
		M1:CmdLCD(CLEAR_LCD);
		StrLCD("Month:(01-12)");
		CmdLCD(GOTO_LINE2_POS0);
		m=read_two_digit();
		if(m<1 || m>12)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid month!");
			delay_ms(100);
			goto M1;
		}
		MONTH=m;															// Set month
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto Y;															// Goto Year
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
	}
		
	Y:CmdLCD(CLEAR_LCD);
		StrLCD("'='year '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				goto Dow;														//Skip Year
		}
		else if(key=='=')
		{
		Y1:CmdLCD(CLEAR_LCD);
		StrLCD("Year(2025-2030)");
		CmdLCD(GOTO_LINE2_POS0);
		y=read_four_digit();
		if(y<2025 || y>2030)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid year!");
			delay_ms(100);
			goto Y1;
		}
		YEAR=y;																	//Set Year
		CmdLCD(CLEAR_LCD);
		StrLCD("'+' next");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'=' stop setting");
		key=KeyScan();
		if(key=='+')
		{
			goto Dow;															// Goto Day
		}
		else if(key=='=')
		{
			CCR = RTC_ENABLE;
			return;
		}
	}
	Dow:CmdLCD(CLEAR_LCD);
		StrLCD("'='Day '-'skip");
		key=KeyScan();
    if(key=='-')
		{
				return;															// Skip Day And stop setting
		}
		else if(key=='=')
		{
		Dow1:CmdLCD(CLEAR_LCD);
		StrLCD("Day:(0-6)");
		CmdLCD(GOTO_LINE2_POS0);
		dow=read_single_digit();
		if(dow<0 || dow>6)
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid day!");
			delay_ms(100);
			goto Dow1;
		}
		DOW=dow;  														// Set Day
	}
    CCR = RTC_ENABLE;											// Start RTC with Modified Values

    CmdLCD(CLEAR_LCD);
    StrLCD("Clock Updated");							// Time Updated Successfully Message to the users
    delay_ms(500);
		return;
}

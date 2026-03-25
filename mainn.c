//main.c

#include <lpc21xx.h>              // LPC21xx microcontroller register definitions
#include "LCD.h"                 // LCD function declarations
#include "KPM.h"                 // Keypad module functions
#include "rtc.h"                 // RTC functions
#include "rtc_defines.h"         // RTC related macros
#include "interrupt.h"           // Interrupt functions
#include "interrupt_defines.h"   // Interrupt pin/channel definitions
#include "medicine.h"            // Medicine reminder logic
#include "rtc_edit.h"            // RTC editing functions
#include "types.h"               // Custom data types (s32, u8, etc.)
#include "LCD_defines.h"         // LCD command macros
#include "delay.h"               // Delay functions
#include "medicine_defines.h"    // Medicine-related macros

extern volatile s32 setup_flag;
// External variable set inside interrupt (EINT0)
// Used to trigger menu when button pressed
//extern volatile s32 buz_flag;

s32 hour,min,sec,date,month,year,day;
// Global variables to store RTC time and date

void port_init()
{
    IODIR1 |= 1<<BUZZER; 
    // Set buzzer pin as OUTPUT
}

void menu()
{
    u8 key;  // Variable to store keypad input

Label:CmdLCD(CLEAR_LCD);  		 // Clear LCD screen
    StrLCD("1.Clock");   			 // Display option 1
    CmdLCD(GOTO_LINE2_POS0);   // Move cursor to second line
    StrLCD("2.Medicine");			 // Display option 2
		StrLCD("3.Exit");          // Display option 3 
    key = KeyScan();				   // Wait and read key from keypad

    if(key=='1')
    {
        edit_rtc_time();     // Call RTC edit function
        CmdLCD(CLEAR_LCD);   // Clear screen after operation
        return;              // Exit menu
    }

    else if(key=='2')
		{
				CmdLCD(CLEAR_LCD);
        configure_medicine(); // Setup medicine schedule
				CmdLCD(CLEAR_LCD);
			return;
		}
		else if(key=='3')
		{
				CmdLCD(CLEAR_LCD);    // Clear screen 
				return;								// Exit menu
		}
		else
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("Invalid Option!"); // Show error message
			delay_ms(100);						 // Small delay
			goto Label;                // Repeat menu
		}
			
}

int main()
{
		s32 i,j;															// Loop variables
		u8 msg[]="Medicine Reminder System!"; // Message to scroll on LCD
		s8 display[17];												// Buffer for 16-char LCD + null terminator
    InitLCD();														// Initialize LCD
    InitKPM();														// Initialize KPM
    RTC_Init();														// Initialize RTc

    port_init();													// Initialize buzzer pin
	
		interrupt_init();											// Initialize interrupts (EINT0,EINT1)
		StrLCD("UserConfigurable");						// Display static message
		for(i=0;i<24+16;i++)									// Total scroll length (message + blank)
		{
			for(j=0;j<16;j++)										// For each LCD column
			{
				if(i+j<16)
					display[j]=' ';									// Initial blank space
				else if(i+j-16<24)
					display[j]=msg[i+j-16];					// Display message characters
				else
					display[j]=' ';									// Ending blank space
			}
			display[16]='\0';										// Null terminate string
			CmdLCD(GOTO_LINE2_POS0);						// Move to second line
			StrLCD(display);        				    // Display scrolling text
			delay_ms(100);											// Control Scrolling speed
		}
		CmdLCD(CLEAR_LCD);										// Clear LCD after scrolling
		
		SetRTCTimeInfo(10,40,00);							// Set time (HH,MIN,SEC)
    SetRTCDateInfo(15,3,2026);						// Set date (DD,MM,YY)
    SetRTCDay(SUN);												// Set Day 
		

    while(1)
    {
        GetRTCTimeInfo(&hour,&min,&sec);  // Read current time from RTC
				DisplayRTCTime(hour,min,sec);			// Display time on LCD	
			
				GetRTCDateInfo(&date,&month,&year); // Read Date
				DisplayRTCDate(date,month,year);    // Display Date
			
				GetRTCDay(&day);										// Read Day	
				DisplayRTCDay(day);									// Display Day

        if(setup_flag)
        {
						IOPIN1^=(1<<EINT0_STATUS_LED);  // Toggle LED when interrupt occurs
            menu();													// Open menu
            setup_flag=0;										// Reset flag
        }
					check_medicine_time(hour,min);    // Check if it's time to take medicine
    }
}

#include <lpc21xx.h>        // LPC21xx registers
#include "lcd.h"            // LCD functions
#include "kpm.h"            // Keypad functions
#include "types.h"          // Data types
#include "lcd_defines.h"    // LCD commands
#include "delay.h"          // Delay functions
#include "medicine_defines.h" // Medicine macros (BUZZER etc.)

struct medicine
{
    s32 hour;								//Medicine hour
    s32 min;								//Medicine minute
};

struct medicine med[3];     // Store upto 3 medicines
s32 med_count=0;						// Number of Medicines stored

extern volatile s32 ack_flag;// Acknowledgement flag(interrupt)
volatile s32 buz_flag=1;		// Buzzer Enable flag

int read_two_digit()
{
    u8 key;
    s32 digits[2];
    s32 i = 0;

    while(i < 3)
    {
			key = KeyScan();				// Get key input

        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';// Convert ASCII to Integer
            CharLCD(key);					// Display
						delay_ms(50);
            i++;
        }
        else if(key == '*')    // BACKSPACE
					{
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left
                CharLCD(' ');   						// erase character
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left again
            }
					}
				else if(key=='=')
					{
						if(i==2)
							break;						// Finish Input
					}
		}
return digits[0]*10 + digits[1]; // Combine Digits
}

s32 read_single_digit()
{
		u8 key;
    s32 digits[1];
    s32 i = 0;

    while(i < 2)
    {
        key = KeyScan();				// Get Key Input

        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';
            CharLCD(key);
						delay_ms(50);
            i++;
        }
				else if(key == '*')    // BACKSPACE
        {
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left
                CharLCD(' ');   						// erase character
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left again
            }
        }
				else if(key=='=')
				{
					if(i==1)
							break;						// Finish Input
				}
	}
	return digits[0];							// Return Digit
}


s32 read_four_digit()
{
		u8 key;
    s32 digits[4];
    s32 i = 0;

    while(i < 5)
    {
        key = KeyScan();					// Get key input
        if(key >= '0' && key <= '9')
        {
            digits[i] = key - '0';
            CharLCD(key);
						delay_ms(50);
            i++;
        }
        else if(key == '*')    // BACKSPACE
        {
            if(i > 0)
            {
                i--;
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left
                CharLCD(' ');   						// erase character
                CmdLCD(SHIFT_DISP_LEFT);   	// cursor left again
            }
        }
				else if(key=='=')
				{
					if(i==4)
							break;
				}
		}
	return ((digits[0]*1000) + (digits[1]*100) + (digits[2]*10) + digits[3]);//Combine Digits
}

void configure_medicine()
{
	u8 key;
label:while(med_count<3)
			{
				mh:																						//To take Hours
				CmdLCD(CLEAR_LCD);
				StrLCD("Medicine");
				CmdLCD(GOTO_LINE1_POS0+9);
				U32LCD(med_count+1);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Hour:(00-23)");
				CmdLCD(GOTO_LINE2_POS0+12);
				med[med_count].hour = read_two_digit();
	
				if(med[med_count].hour<0 || med[med_count].hour>23)		// Takes Hour(00-23)
				{
					CmdLCD(CLEAR_LCD);
					StrLCD("Invalid Hour!");
					delay_ms(500);
					CmdLCD(CLEAR_LCD);
					goto mh;
				}
				mm:																								// To take Minutes
				CmdLCD(CLEAR_LCD);								
				StrLCD("Medicine");
				CmdLCD(GOTO_LINE1_POS0+9);
				U32LCD(med_count+1);
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("Minute:(00-59)");
				CmdLCD(GOTO_LINE2_POS0+14);
				med[med_count].min = read_two_digit();

				if(med[med_count].min<0 || med[med_count].min>59) //Takes min (00-59)
				{
					CmdLCD(CLEAR_LCD);
					StrLCD("Invalid Minute!");
					delay_ms(500);
					CmdLCD(CLEAR_LCD);
					goto mm;
				}

				med_count++;
				
		if(med_count<=2)									//Takes 3 medicine schedules only 
		{
		CmdLCD(CLEAR_LCD);
		StrLCD("'+'Add Medicine");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("'='Stop setting!");
		key=KeyScan();
		if(key=='+')
		{
			goto label;
		}
		if(key=='=')
		{
			return;
		}
		}
	}
    CmdLCD(CLEAR_LCD);
    StrLCD("Saved");								// Display After entering all medicine schedules
    delay_ms(500);
}

void alert_user()
{
    s32 t = 60;										// Alert Duration
    CmdLCD(CLEAR_LCD);
    StrLCD("Take Medicine");

    while(t--)
    {
        IOSET1 = 1<<BUZZER;   // buzzer ON
        delay_ms(200);

        IOCLR1 = 1<<BUZZER;   // buzzer OFF
        delay_ms(200);

        if(ack_flag)      // Stop if user presses Switch2
        {
          ack_flag = 0;
					buz_flag=0;
					IOCLR1 = 1<<BUZZER;
						
						break;
        }
    }
    IOCLR1 = 1<<BUZZER;		// Ensure buzzer OFF
		CmdLCD(CLEAR_LCD);
		return;
}

void check_medicine_time(s32 h,s32 m)
{
    s32 i;
		for(i=0;i<med_count;i++)
    {
			if(i==1 || i==2)
			{
				buz_flag=1;					// Re-enable buzzer for next meds
			}
				if(h==med[i].hour && m==med[i].min)
					{
						if(buz_flag)
						{
							alert_user();		 // Trigger alert
						}
        }
    }
}

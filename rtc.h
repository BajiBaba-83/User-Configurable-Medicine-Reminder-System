#include"types.h"
void RTC_Init(void);											//Function to Initialize RTC
void GetRTCTimeInfo(s32 *,s32 *,s32 *);		//Function to get time(hour,min,sec) from RTC Registers
void DisplayRTCTime(u32,u32,u32);					//Function to Display RTC time info on LCD	
void GetRTCDateInfo(s32 *,s32 *,s32 *);		//Function to get date(date,month,year) from RTC Registers
void DisplayRTCDate(u32,u32,u32);					//Function to Display RTC date info on LCD

void SetRTCTimeInfo(u32,u32,u32);					//Function to set time(hour,min,sec) from the user
void SetRTCDateInfo(u32,u32,u32);					//Function to set date(date,month,year) from the user

void GetRTCDay(s32 *);										//Function to get day from RTC Registers
void DisplayRTCDay(u32);									//Function to display RTC day on LCD
void SetRTCDay(u32);											//Function to set Day from the user

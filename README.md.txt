 Medicine Reminder System (LPC2148)

Project Overview

The User Configurable Medicine Reminder System is an embedded system project using the LPC2148 ARM7 microcontroller. It alerts users to take medicines on time using a buzzer and LCD display.

Features
-   Real-Time Clock (RTC)
-   Buzzer alert system
-   LCD display interface
-   External interrupt to stop buzzer
-   User input for time setting.

 Hardware Requirements

-   LPC2148 Microcontroller
-   16x2 LCD
-   Buzzer
-   Push Buttons
-   Power Supply

 Software Requirements

-   Keil µVision
-   Flash Magic

 Project Structure

medicine-reminder-system/
?
??? main.c # Main program logic
??? lcd.c # LCD interfacing functions
??? lcd.h
??? rtc.c # RTC configuration and time handling
??? rtc.h
??? interrupt.c # External interrupt handling
??? buzzer.c # Buzzer control logic
??? keypad.c # Keypad input handling (if used)
??? README.md







 Working

1.  Initialize system
2.  Set time and reminder
3.  Monitor RTC
4.  Trigger buzzer when time matches
5.  Stop using interrupt

 How to Run

1.  Compile in Keil
2.  Generate HEX
3.  Flash using Flash Magic

Author

K. Baji Baba


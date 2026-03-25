//LCD_defines.h

#define LCD_DATA 8     // LCD data pins start from P0.8 to P0.15 (8-bit mode)
#define RS 16          // Register Select pin connected to P0.16
#define RW 17          // Read/Write pin connected to P0.17
#define EN 18          // Enable pin connected to P0.18

//lcd_commands
#define CLEAR_LCD 0X01            // Clear display
#define RET_CUR_HOME 0x02         // Return cursor to home position
#define DISP_OFF 0x08             // Display OFF
#define DISP_ON 0x0C              // Display ON, cursor OFF
#define DISP_ON_CUR_ON 0x0E       // Display ON, cursor ON
#define DISP_ON_CUR_BLINK 0x0F    // Display ON, cursor blinking
#define MODE_8BIT_1LINE 0X30      // 8-bit mode, 1 line
#define MODE_8BIT_2LINE 0X38      // 8-bit mode, 2 lines
#define MODE_4BIT_1LINE 0X20      // 4-bit mode, 1 line
#define MODE_4BIT_2LINE 0X28      // 4-bit mode, 2 lines
#define GOTO_LINE1_POS0 0X80      // Cursor line 1, position 0
#define GOTO_LINE2_POS0 0XC0      // Cursor line 2, position 0
#define GOTO_LINE3_POS0 0X94      // Cursor line 3
#define GOTO_LINE4_POS0 0XD4      // Cursor line 4
#define SHIFT_CUR_RIGHT 0X06      // Cursor moves right
#define SHIFT_DISP_LEFT 0x10      // Shift display left
#define SHIFT_DISP_RIGHT 0X14     // Shift display right
#define GOTO_CGRAM 0x40           // Access CGRAM for custom characters

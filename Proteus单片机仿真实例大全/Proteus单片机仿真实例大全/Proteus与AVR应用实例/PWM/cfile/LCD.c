// ************************************************
// *** 采用4位数据线的1602液晶驱动程序 ***
// *** LCD.C ***
// ************************************************
#define ENABLE_BIT_DEFINITIONS
#define LCD_C
#include "includes.h"
// ***** Define I/O pins ***** //
#define BIT7 0x80
#define BIT6 0x40
#define BIT5 0x20
#define BIT4 0x10
#define BIT3 0x08
#define BIT2 0x04
#define BIT1 0x02
#define BIT0 0x01
// *** Set port for LCD Data Bus 8 bit mode *** //
#define LCD_OP_PORT PORTB
#define LCD_IP_PORT PINB
#define LCD_DIR_PORT DDRB
// *** Set LCD Enable Port and Bit values *** //
//#define LCD_EN LCD_OP_PORT.2
// *** Set LCD Register Select Port and Bit values *** //
//#define LCD_RS LCD_OP_PORT.0
// *** Set LCD Read/Write Port and Bit values *** //
//#define LCD_RW LCD_OP_PORT.1
/****************************************************************/
 
 #define LCD_EN  (1 << 2)     //引脚定义
 #define LCD_RS (1 << 0)
 #define LCD_RW (1 << 1)
 
 #define lcd_set_e()  (LCD_OP_PORT |= LCD_EN)   //置位与清零
 #define lcd_set_rs() (LCD_OP_PORT |= LCD_RS)
 #define lcd_set_rw() (LCD_OP_PORT |= LCD_RW)
 #define lcd_clear_e()  (LCD_OP_PORT &= ~LCD_EN)
 #define lcd_clear_rs() (LCD_OP_PORT &= ~LCD_RS)
 #define lcd_clear_rw() (LCD_OP_PORT &= ~LCD_RW)
/****************************************************************/

#define LCD_ON 0x0C
#define LCD_CURS_ON 0x0D
#define LCD_OFF 0x08
#define LCD_HOME 0x02
#define LCD_CLEAR 0x01
#define LCD_NEW_LINE 0xC0
#define LCD_FUNCTION_SET 0x28
#define LCD_MODE_SET 0x06


void LCD_INIT(void)
{
LCD_DIR_PORT = 0xff; // LCD port output
LCD_OP_PORT = 0x30; // Load high-data to port
lcd_clear_rw(); // Set LCD to write
lcd_clear_rs(); // Set LCD to command
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
delay_nus(40);
lcd_clear_rw() ; // Set LCD to write
lcd_clear_rs(); // Set LCD to command
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
delay_nus(40);
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
delay_nus(40);
LCD_OP_PORT = 0x20;
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
delay_nus(40);
}
//*****************************************************//
// This routine will return the busy flag from the LCD //
//*****************************************************//
void LCD_Busy ( void )
{
unsigned char temp,high;
unsigned char low;
LCD_DIR_PORT = 0x0f; // Make I/O Port input
do
{
temp=LCD_OP_PORT;
temp=temp&BIT3;
LCD_OP_PORT=temp;
lcd_set_rw(); // Set LCD to READ
lcd_clear_rs();
lcd_set_e();
delay_nus(3);
high = LCD_IP_PORT; // read the high nibble.
lcd_clear_e(); // Disable LCD
lcd_set_e();
asm("nop");
asm("nop");
low = LCD_IP_PORT; // read the low nibble.
lcd_clear_e(); // Disable LCD
} while(high & 0x80);
delay_nus(20);
}
// ********************************************** //
// *** Write a control instruction to the LCD *** //
// ********************************************** //
void LCD_WriteControl (unsigned char CMD)
{
char temp;
LCD_Busy(); // Test if LCD busy
LCD_DIR_PORT = 0xff; // LCD port output
temp=LCD_OP_PORT;
temp=temp&BIT3;
LCD_OP_PORT =(CMD & 0xf0)|temp; // Load high-data to port
lcd_clear_rw(); // Set LCD to write
lcd_clear_rs(); // Set LCD to command
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
LCD_OP_PORT =(CMD<<4)|temp; // Load low-data to port
lcd_clear_rw(); // Set LCD to write
lcd_clear_rs(); // Set LCD to command
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
}
// ***************************************** //
// *** Write one byte of data to the LCD *** //
// ***************************************** //
void LCD_WriteData (unsigned char Data)
{
char temp;
LCD_Busy(); // Test if LCD Busy
LCD_DIR_PORT = 0xFF; // LCD port output
temp=LCD_OP_PORT;
temp=temp&BIT3;
LCD_OP_PORT =(Data & 0xf0)|temp; // Load high-data to port
lcd_clear_rw() ; // Set LCD to write
lcd_set_rs(); // Set LCD to data
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
LCD_OP_PORT = (Data << 4)|temp; // Load low-data to port
lcd_clear_rw() ; // Set LCD to write
lcd_set_rs(); // Set LCD to data
lcd_set_e(); // Write data to LCD
asm("nop");
asm("nop");
lcd_clear_e(); // Disable LCD
}
// ********************************* //
// *** Initialize the LCD driver *** //
// ********************************* //
void Init_LCD(void)
{
LCD_INIT();
LCD_WriteControl (LCD_FUNCTION_SET);
LCD_WriteControl (LCD_OFF);
LCD_WriteControl (LCD_CLEAR);
LCD_WriteControl (LCD_MODE_SET);
LCD_WriteControl (LCD_ON);
LCD_WriteControl (LCD_HOME);
}
// ************************************************ //
// *** Clear the LCD screen (also homes cursor) *** //
// ************************************************ //
void LCD_Clear(void)
{
LCD_WriteControl(0x01);
}
// *********************************************** //
// *** Position the LCD cursor at row 1, col 1 *** //
// *********************************************** //
void LCD_Home(void)
{
LCD_WriteControl(0x02);
}
// ****************************************************************** //
// *** Display a single character, at the current cursor location *** //
// ****************************************************************** //
void LCD_DisplayCharacter (char Char)
{
LCD_WriteData (Char);
}
// ********************************************************************* //
// *** Display a string at the specified row and column, using FLASH *** //
// ********************************************************************* //
void LCD_DisplayString_F (char row, char column , unsigned char __flash *string)
{
LCD_Cursor (row, column);
while (*string)
{
LCD_DisplayCharacter (*string++);
}
}
// ******************************************************************* //
// *** Display a string at the specified row and column, using RAM *** //
// ******************************************************************* //
void LCD_DisplayString (char row, char column ,unsigned char *string)
{
LCD_Cursor (row, column);
while (*string)
LCD_DisplayCharacter (*string++);
}
// *************************************************** //
// *** Position the LCD cursor at "row", "column". *** //
// *************************************************** //
void LCD_Cursor (char row, char column)
{
switch (row) {
case 1: LCD_WriteControl (0x80 + column - 1); break;
case 2: LCD_WriteControl (0xc0 + column - 1); break;
case 3: LCD_WriteControl (0x94 + column - 1); break;
case 4: LCD_WriteControl (0xd4 + column - 1); break;
default: break;
}
}
// ************************** //
// *** Turn the cursor on *** //
// ************************** //
void LCD_Cursor_On (void)
{
LCD_WriteControl (LCD_CURS_ON);
}
// *************************** //
// *** Turn the cursor off *** //
// *************************** //
void LCD_Cursor_Off (void)
{
LCD_WriteControl (LCD_ON);
}
// ******************** //
// *** Turn Off LCD *** //
// ******************** //
void LCD_Display_Off (void)
{
LCD_WriteControl(LCD_OFF);
}
// ******************* //
// *** Turn On LCD *** //
// ******************* //
void LCD_Display_On (void)
{
LCD_WriteControl(LCD_ON);
}
// ******************* //
// *** Clear line *** //
// ******************* //
void ClearLine(unsigned char line)
{
    unsigned char *space="                ";
    LCD_DisplayString(line,1,space);
}
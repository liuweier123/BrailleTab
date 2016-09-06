// ************************************************
// *** LCD_4BIT Driver V1.0 ***
// *** LCD.H ***
// ************************************************
/* LCD data bus, 4 bit mode */
// *** LCD Function *** //
//#pragma used+
#ifndef LCD_H
#define LCD_H

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
#define LCD_MODE_SET  0x06
/**********************************************************/

#if defined LCD_C
void init_usart(void);
int usart_putchar(char);
void Init_LCD(void);
void LCD_WriteControl (unsigned char CMD);
void LCD_Display_Off(void);
void LCD_Display_On(void);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Cursor(char row, char column);
void LCD_Cursor_On(void);
void LCD_Cursor_Off(void);
void LCD_DisplayCharacter(char Char);
void LCD_DisplayString_F(char row, char column, unsigned char __flash *string);
void LCD_DisplayString(char row, char column, unsigned char *string);
#else
extern void init_usart(void);
extern int usart_putchar(char);
extern void Init_LCD(void);
extern void LCD_WriteControl (unsigned char CMD);
extern void LCD_Display_Off(void);
extern void LCD_Display_On(void);
extern void LCD_Clear(void);
extern void LCD_Home(void);
extern void LCD_Cursor(char row, char column);
extern void LCD_Cursor_On(void);
extern void LCD_Cursor_Off(void);
extern void LCD_DisplayCharacter(char Char);
extern void LCD_DisplayString_F(char row, char column, unsigned char __flash *string);
extern void LCD_DisplayString(char row, char column, unsigned char *string);
#endif
#endif
//#pragma used-

// ************************************************
// *** LCD_4BIT Driver V1.0 ***
// *** LCD.H ***
// ************************************************
/* LCD data bus, 4 bit mode */
// *** LCD Function *** //
//#pragma used+
#ifndef LCD_H
#define LCD_H
#ifdef LCD_C
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
void ClearLine(unsigned char line);
#else
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
extern void ClearLine(unsigned char line);
#endif
#endif
//#pragma used-

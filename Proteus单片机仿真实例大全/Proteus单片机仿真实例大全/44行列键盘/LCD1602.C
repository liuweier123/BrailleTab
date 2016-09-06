/*---------------------------------------------------------------------
                         LCD1602.C文件 LCD1602的函数  
  作者：Computer-lov     创建日期:2004.11.12    最后修改日期:2004.11.12
  版本：1.0
----------------------------------------------------------------------*/

#include "hardware.h"
#include "lcd1602.h"

void LCD_check_busy(void)   //检测LCD状态，看它是不是还在忙呢
{
 while(1)
  {
   LCD_EN=0;
   LCD_RS=0;
   LCD_RW=1;
   LCD_DATA=0xff;
   LCD_EN=1;
   if(!LCD_BUSY)break;
  }
 LCD_EN=0;
}

void LCD_cls(void)          //LCD清屏
{
 
 LCD_check_busy();
 LCD_RS=0;
 LCD_RW=0;
 LCD_DATA=1;
 LCD_EN=1;
 LCD_EN=0;
 
}

void LCD_write_instruction(unsigned char LCD_instruction)   //写指令到LCD
{
  LCD_check_busy();
 LCD_RS=0;
 LCD_RW=0;
 
 LCD_DATA=LCD_instruction;
 LCD_EN=1;
 LCD_EN=0;
 }

void LCD_write_data(unsigned char LCD_data)      //输出一个字节数据到LCD
{
  LCD_check_busy();
 LCD_RS=1;
 LCD_RW=0;
 
 LCD_DATA=LCD_data;
 LCD_EN=1;
 LCD_EN=0;
 }
 
void LCD_set_position(unsigned char x)            //LCD光标定位到x处
{
 LCD_write_instruction(0x80+x);
}

/*
void LCD_go_home(void)                         //LCD光标归位
{
 LCD_write_instruction(LCD_GO_HOME);
}
*/

void LCD_printc(unsigned char lcd_data)          //输出一个字符到LCD
{
 LCD_write_data(lcd_data);
}

void LCD_prints(unsigned char *lcd_string)       //输出一个字符串到LCD
{
 unsigned char i=0;
 while(lcd_string[i]!=0x00)
  {
   LCD_write_data(lcd_string[i]);
   i++;
  } 
}

void LCD_initial(void)                        //初始化LCD
{
 LCD_write_instruction(LCD_AC_AUTO_INCREMENT|LCD_MOVE_DISENABLE);
 LCD_write_instruction(LCD_DISPLAY_ON|LCD_CURSOR_OFF);
 LCD_write_instruction(LCD_DISPLAY_DOUBLE_LINE);
 LCD_cls();
}
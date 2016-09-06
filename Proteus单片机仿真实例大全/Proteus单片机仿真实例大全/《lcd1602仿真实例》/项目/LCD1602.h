/*---------------------------------------------------------------------
                         LCD1602.H文件 LCD1602的一些命令定义
  作者：Computer-lov     创建日期:2004.11.12    最后修改日期:2004.11.22
  版本：1.0
----------------------------------------------------------------------*/

#ifndef __LCD_H__
#define __LCD_H__

#define LCD_GO_HOME               0x02         //AC=0，光标、画面回HOME位

//输入方式设置
#define LCD_AC_AUTO_INCREMENT     0x06         //数据读、写操作后，AC自动增一
#define LCD_AC_AUTO_DECREASE      0x04         //数据读、写操作后，AC自动减一
#define LCD_MOVE_ENABLE           0x05         //数据读、写操作，画面平移
#define LCD_MOVE_DISENABLE        0x04         //数据读、写操作，画面不动

//设置显示、光标及闪烁开、关
#define LCD_DISPLAY_ON            0x0C         //显示开
#define LCD_DISPLAY_OFF           0x08         //显示关
#define LCD_CURSOR_ON             0x0A         //光标显示
#define LCD_CURSOR_OFF            0x08         //光标不显示
#define LCD_CURSOR_BLINK_ON       0x09         //光标闪烁
#define LCD_CURSOR_BLINK_OFF      0x08         //光标不闪烁

//光标、画面移动，不影响DDRAM
#define LCD_LEFT_MOVE             0x18         //LCD显示左移一位
#define LCD_RIGHT_MOVE            0x1C         //LCD显示右移一位
#define LCD_CURSOR_LEFT_MOVE      0x10         //光标左移一位
#define LCD_CURSOR_RIGHT_MOVE     0x14         //光标右移一位

//工作方式设置
#define LCD_DISPLAY_DOUBLE_LINE   0x38         //两行显示
#define LCD_DISPLAY_SINGLE_LINE   0x30         //单行显示
void LCD_cls(void);
void LCD_write_data(unsigned char);
void LCD_initial(void);
void LCD_set_position(unsigned char);
void LCD_prints(unsigned char *);
void LCD_printc(unsigned char); 

#endif

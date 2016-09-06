#ifndef __LCD_H__
#define __LCD_H__

// LCD128*64 数据线
#define LCD_P		P1
// LCD128*64 I/O 信号管脚
sbit DI = P2^0; // 数据\指令 选择
sbit RW = P2^2; // 读\写 选择
sbit EN = P2^1; // 读\写使能
sbit CS1= P2^3; // 片选1,低有效(前64列)
sbit CS2= P2^4; // 片选2,低有效(后64列)

//函数声明================================
//设定行地址(页)--X 0-7
void SetLine(uchar line);
//设定列地址--Y 0-63
void SetColumn(uchar column);
//设定显示开始行--XX
void SetStartLine(uchar startline); //0--63
//开关显示
void SetOnOff(uchar onoff);
//选择屏幕
//screen: 0-全屏,1-左屏,2-右屏
void SelectScreen(uchar screen);
//清屏
//screen: 0-全屏,1-左屏,2-右
void ClearScreen(uchar screen);
//显示8*8点阵
//lin:行(0-7), column: 列(0-127)
//address : 字模区首地址
void Show8x8(uchar lin,uchar column,uchar *address);
/*//显示数字8*16
void ShowNumber(uchar lin,uchar column,uchar num);*/
//显示汉字16*16
void ShowChina(uchar lin,uchar column,uchar num);
void InitLCD(void); //初始化LCD
/*void r_show8x8(uchar lin,uchar column,uchar *address);
void r_ShowNumber(uchar lin,uchar column,uchar num);*/
//显示图片
//lin:行(0-7), column: 列(0-127)
//high:高度, width:宽度(要为8的倍数)
//address : 图片区首地址
void ShowPicture(uchar lin, uchar column, uchar high, uchar width, uchar *address);
#endif
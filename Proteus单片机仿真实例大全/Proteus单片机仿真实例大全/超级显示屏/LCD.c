#include"REG51F.h"
#include"intrins.h"
#include"USEH1.h"
#include"lcd.h"
#include"HZcode.h"

bit busy_bit=1;
//函数声明==============================
void nop(void);
bit CheckBusy(void); //状态检查
//写显示数据
//dat:显示数据
void WriteByte(uchar dat);
//向LCD发送命令
//command :命令
SendCommandToLCD(uchar command);

//函数定义==============================
void nop(void)
{
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
}
//状态检查
bit CheckBusy(void)
{
   uchar state=0;

   P1=0xFF;//空读操作
   RW=1;
   DI=0;
   EN=1;
   state=P1;
   EN=0;

   P1=0xFF;//再读才有效
   RW=1;
   DI=0;
   EN=1;
   state=P1;
   EN=0;
   busy_bit=(bit)(state>>7);
   return(busy_bit);
}

//写显示数据
//dat:显示数据
void WriteByte(uchar dat)
{
   while(CheckBusy());
   DI=1;
   RW=0;
   LCD_P=dat;
   EN=1;
   EN=0;
}
/*-----------------------------------------------------------------------------------------------------*/
//向LCD发送命令
//command :命令
SendCommandToLCD(uchar command)
{
   while(CheckBusy());
   RW=0;
   DI=0;
   LCD_P=command;
   EN=1;
   EN=0;
}
/*----------------------------------------------------------------------------------------------------*/
//设定行地址(页)--X 0-7
void SetLine(uchar line)
{
   line &= 0x07; // 0<=line<=7
   line |= 0xb8; //1011 1xxx
   SendCommandToLCD(line);
}
//设定列地址--Y 0-63
void SetColumn(uchar column)
{
   column &= 0x3f; // 0=<column<=63
   column |= 0x40; //01xx xxxx
   SendCommandToLCD(column);
}
//设定显示开始行--XX
void SetStartLine(uchar startline) //0--63
{
   //startline &= 0x07;
   startline |= 0xc0; //1100 0000
   SendCommandToLCD(startline);
}
//开关显示
void SetOnOff(uchar onoff)
{
   onoff|=0x3e; //0011 111x
   SendCommandToLCD(onoff);
}
/*---------------------------------------------------------------------------------------------------*/
//选择屏幕
//screen: 0-全屏,1-左屏,2-右屏
void SelectScreen(uchar screen)
{ //北京显示器:负有效 CS1: 0--右; CS2: 0--左
   switch(screen)
   {
      case 0:
         CS1=0;//全屏
         nop();
         CS2=0;
         nop();
         break;
      case 1:
         CS1=1;//左屏
         nop();
         CS2=0;
         nop();
         break;
      case 2:
         CS1=0;//右屏
         nop();
         CS2=1;
         nop();
         break;
      default:
         break;
   }
}
/*---------------------------------------------------------------------------------------------------*/
//清屏
//screen: 0-全屏,1-左屏,2-右
void ClearScreen(uchar screen)
{
   uchar i,j;
   SelectScreen(screen);
   for(i=0;i<8;i++)
   {
      SetLine(i);
      for(j=0;j<64;j++)
      {
      	 SetColumn(j);
         WriteByte(0x00);
      }
   }
}
/*--------------------------------------------------------------------------------------------------*/
//显示8*8点阵
//lin:行(0-7), column: 列(0-127)
//address : 字模区首地址
void Show8x8(uchar lin,uchar column,uchar *address)
{
   uchar i;
   //if(column>128) {return;}
   if(column<64)
   {
      SelectScreen(1); //如果列数<64则从第一屏上开始写
      SetLine(lin);
      SetColumn(column);
      for(i=0;i<8;i++)
      {
         if(column+i<64)
         {
            WriteByte(*(address+i));
         }
         else
         {
            SelectScreen(2);
            SetLine(lin);
            SetColumn(column-64+i);
            WriteByte(*(address+i));
         }
      }
   }
   else
   {
      SelectScreen(2); //否则从第二屏上开始写
      column-=64; //防止越界
      SetLine(lin);
      SetColumn(column);
      for(i=0;i<8;i++)
      {
         if(column+i<64)
         {
            WriteByte(*(address+i));
         }
         else
         {
            SelectScreen(1);
            SetLine(lin);
            SetColumn(column-64+i);
            WriteByte(*(address+i));
         }
      }
   }
}
/*--------------------------------------------------------------------------------------------------*/
/*//显示数字8*16
void ShowNumber(uchar lin,uchar column,uchar num)
{
   uchar *address;
   address=&Numcode[num][0];
   Show8x8(lin,column,address);
   Show8x8(lin+1,column,address+8);
}*/
/*--------------------------------------------------------------------------------------------------*/
//显示汉字16*16
void ShowChina(uchar lin,uchar column,uchar num)
{
   uchar *address;
   //if(lin>7 || column>127){return;}
   address = &HZcode[num][0];
   Show8x8(lin,column,address);
   Show8x8(lin,column+8,address+8);
   Show8x8(lin+1,column,address+16);
   Show8x8(lin+1,column+8,address+24);
}
/*--------------------------------------------------------------------------------------------------*/
void InitLCD(void) //初始化LCD
{
   uchar i=2000; //延时
   while(i--);
   SetOnOff(1); //开显示
   ClearScreen(1);//清屏
   ClearScreen(2);
   SetStartLine(0); //开始行:0
}
/*--------------------------------------------------------------------------------------------------*/
/*void r_show8x8(uchar lin,uchar column,uchar *address)
{
   uchar i,r_data;
   if(column<64)
   {
      SelectScreen(1); //如果列数<64则从第一屏上开始写
      SetLine(lin);
      SetColumn(column);
      for(i=0;i<8;i++)
      {
         if(column+i<64)
         {
            r_data = ~(*(address+i));
            WriteByte(r_data);
         }
         else
         {
            SelectScreen(2);
            SetLine(lin);
            SetColumn(column-64+i);
            r_data = ~(*(address+i));
            WriteByte(r_data);
         }
      }
   }
   else
   {
      SelectScreen(2); //否则从第二屏上开始写
      column-=64; //防止越界
      SetLine(lin);
      SetColumn(column);
      for(i=0;i<8;i++)
      {
         if(column+i<64)
         {
            r_data = ~(*(address+i));
            WriteByte(r_data);
         }
         else
         {
            SelectScreen(1);
            SetLine(lin);
            SetColumn(column-64+i);
            r_data = ~(*(address+i));
            WriteByte(r_data);
         }
      }
   }
}*/
/*--------------------------------------------------------------------------------------------------*/
/*void r_ShowNumber(uchar lin,uchar column,uchar num)
{
   uchar *address;
   address=&Numcode[num][0];
   r_show8x8(lin,column,address);
   r_show8x8(lin+1,column,address+8);
}*/
/*--------------------------------------------------------------------------------------------------*/
//显示图片
//lin:行(0-7), column: 列(0-127)
//high:高度, width:宽度(要为8的倍数)
//address : 图片区首地址
void ShowPicture(uchar lin, uchar column, uchar high, uchar width, uchar *address)
{
   uchar i, j;
   //if(column>128) {return;}
   if(column<64)
   {
      for(j=0;j<high;j+=8)
      {
      	 SelectScreen(1); //如果列数<64则从第一屏上开始写
         SetLine(lin);
         SetColumn(column);
         for(i=0;i<width;i++)
         {
            if(i+column>127)
               break;
            if(column+i<64)
            {
               WriteByte(*(address+i));
            }
            else
            {
               SelectScreen(2);
               SetLine(lin);
               SetColumn(column-64+i);
               WriteByte(*(address+i));
            }
         }
         lin+=1;
         address+=width;
      }
   }
   else
   {
      column-=64; //防止越界
      for(j=0;j<high;j+=8)
      {
      	 SelectScreen(2); //否则从第二屏上开始写
         SetLine(lin);
         SetColumn(column);
         for(i=0;i<width;i++)
         {
         	 if(i+column>64)
               break;
            if(column+i<64)
            {
               WriteByte(*(address+i));
            }
            else
            {
               SelectScreen(1);
               SetLine(lin);
               SetColumn(column-64+i);
               WriteByte(*(address+i));
            }
         }
         lin+=1;
         address+=width;
     }
   }
}
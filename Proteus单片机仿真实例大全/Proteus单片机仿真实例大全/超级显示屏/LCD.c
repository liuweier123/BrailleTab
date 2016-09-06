#include"REG51F.h"
#include"intrins.h"
#include"USEH1.h"
#include"lcd.h"
#include"HZcode.h"

bit busy_bit=1;
//��������==============================
void nop(void);
bit CheckBusy(void); //״̬���
//д��ʾ����
//dat:��ʾ����
void WriteByte(uchar dat);
//��LCD��������
//command :����
SendCommandToLCD(uchar command);

//��������==============================
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
//״̬���
bit CheckBusy(void)
{
   uchar state=0;

   P1=0xFF;//�ն�����
   RW=1;
   DI=0;
   EN=1;
   state=P1;
   EN=0;

   P1=0xFF;//�ٶ�����Ч
   RW=1;
   DI=0;
   EN=1;
   state=P1;
   EN=0;
   busy_bit=(bit)(state>>7);
   return(busy_bit);
}

//д��ʾ����
//dat:��ʾ����
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
//��LCD��������
//command :����
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
//�趨�е�ַ(ҳ)--X 0-7
void SetLine(uchar line)
{
   line &= 0x07; // 0<=line<=7
   line |= 0xb8; //1011 1xxx
   SendCommandToLCD(line);
}
//�趨�е�ַ--Y 0-63
void SetColumn(uchar column)
{
   column &= 0x3f; // 0=<column<=63
   column |= 0x40; //01xx xxxx
   SendCommandToLCD(column);
}
//�趨��ʾ��ʼ��--XX
void SetStartLine(uchar startline) //0--63
{
   //startline &= 0x07;
   startline |= 0xc0; //1100 0000
   SendCommandToLCD(startline);
}
//������ʾ
void SetOnOff(uchar onoff)
{
   onoff|=0x3e; //0011 111x
   SendCommandToLCD(onoff);
}
/*---------------------------------------------------------------------------------------------------*/
//ѡ����Ļ
//screen: 0-ȫ��,1-����,2-����
void SelectScreen(uchar screen)
{ //������ʾ��:����Ч CS1: 0--��; CS2: 0--��
   switch(screen)
   {
      case 0:
         CS1=0;//ȫ��
         nop();
         CS2=0;
         nop();
         break;
      case 1:
         CS1=1;//����
         nop();
         CS2=0;
         nop();
         break;
      case 2:
         CS1=0;//����
         nop();
         CS2=1;
         nop();
         break;
      default:
         break;
   }
}
/*---------------------------------------------------------------------------------------------------*/
//����
//screen: 0-ȫ��,1-����,2-��
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
//��ʾ8*8����
//lin:��(0-7), column: ��(0-127)
//address : ��ģ���׵�ַ
void Show8x8(uchar lin,uchar column,uchar *address)
{
   uchar i;
   //if(column>128) {return;}
   if(column<64)
   {
      SelectScreen(1); //�������<64��ӵ�һ���Ͽ�ʼд
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
      SelectScreen(2); //����ӵڶ����Ͽ�ʼд
      column-=64; //��ֹԽ��
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
/*//��ʾ����8*16
void ShowNumber(uchar lin,uchar column,uchar num)
{
   uchar *address;
   address=&Numcode[num][0];
   Show8x8(lin,column,address);
   Show8x8(lin+1,column,address+8);
}*/
/*--------------------------------------------------------------------------------------------------*/
//��ʾ����16*16
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
void InitLCD(void) //��ʼ��LCD
{
   uchar i=2000; //��ʱ
   while(i--);
   SetOnOff(1); //����ʾ
   ClearScreen(1);//����
   ClearScreen(2);
   SetStartLine(0); //��ʼ��:0
}
/*--------------------------------------------------------------------------------------------------*/
/*void r_show8x8(uchar lin,uchar column,uchar *address)
{
   uchar i,r_data;
   if(column<64)
   {
      SelectScreen(1); //�������<64��ӵ�һ���Ͽ�ʼд
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
      SelectScreen(2); //����ӵڶ����Ͽ�ʼд
      column-=64; //��ֹԽ��
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
//��ʾͼƬ
//lin:��(0-7), column: ��(0-127)
//high:�߶�, width:���(ҪΪ8�ı���)
//address : ͼƬ���׵�ַ
void ShowPicture(uchar lin, uchar column, uchar high, uchar width, uchar *address)
{
   uchar i, j;
   //if(column>128) {return;}
   if(column<64)
   {
      for(j=0;j<high;j+=8)
      {
      	 SelectScreen(1); //�������<64��ӵ�һ���Ͽ�ʼд
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
      column-=64; //��ֹԽ��
      for(j=0;j<high;j+=8)
      {
      	 SelectScreen(2); //����ӵڶ����Ͽ�ʼд
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
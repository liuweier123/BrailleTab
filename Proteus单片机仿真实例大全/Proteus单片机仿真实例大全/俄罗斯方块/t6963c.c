#include <AT89X52.h>	
#include "t6963c.h"
#include "fangkuai.h"
#include "typedef.h"

static uint txthome=0x0000;
static uint grshome=0x1000;

//LCD�ӿڶ���
sfr   PORTD = 0x90 ;
sbit  PCD = P2^7 ;
sbit  PWR = P2^5 ;
sbit  PRD = P2^6 ;

//��������
unsigned char code CCTable[] = {
/*��   CB7EB */
0x00,0x47,0x20,0x29,0x09,0x09,0x11,0x13,0x21,0xE0,0x2F,0x20,0x20,0x20,0x20,0x20,
0x00,0xF8,0x08,0x08,0x10,0x10,0x10,0xFC,0x04,0x04,0xF4,0x04,0x04,0x04,0x28,0x10,

/*��   CD1E0 */
0x04,0x04,0xFF,0x04,0x17,0x10,0xF7,0x14,0x34,0xD7,0x00,0x28,0x24,0x66,0xC2,0x00,
0x40,0x40,0xFE,0x40,0xC0,0x14,0xDE,0x50,0x52,0xCE,0x00,0x88,0x44,0x66,0x22,0x00,

/*��   CBBD4 */
0x10,0x13,0x96,0x58,0x51,0xFE,0x28,0x28,0x29,0x28,0x28,0x2B,0x4C,0x48,0x80,0x00,
0x00,0xFE,0x44,0x40,0xFC,0x40,0xA0,0xA0,0xFC,0x20,0x20,0xFE,0x20,0x20,0x20,0x20,

/*��   CD6C6 */
0x24,0x34,0x24,0x3F,0x44,0x04,0x7F,0x04,0x3F,0x24,0x24,0x24,0x24,0x27,0x05,0x04,
0x04,0x04,0x24,0xA4,0x24,0x24,0xA4,0x24,0xA4,0xA4,0xA4,0xA4,0x84,0x84,0x14,0x08,

/*��   CD7F7 */
0x08,0x0C,0x09,0x13,0x12,0x34,0x50,0x90,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x80,0x80,0x00,0xFE,0x80,0x88,0xFC,0x80,0x80,0x84,0xFE,0x80,0x80,0x80,0x80,0x80,

/*��   CB5C3 */
0x13,0x1A,0x23,0x4A,0x8B,0x10,0x13,0x30,0x50,0x97,0x10,0x11,0x11,0x11,0x10,0x10,
0xF8,0x08,0xF8,0x08,0xF8,0x00,0xFE,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x50,0x20,

/*��   CB7D6 */
0x08,0x0C,0x08,0x10,0x10,0x20,0x40,0x9F,0x04,0x04,0x04,0x04,0x08,0x10,0x20,0x40,
0x80,0x80,0x40,0x20,0x30,0x18,0x0E,0xE4,0x20,0x20,0x20,0x20,0x20,0xA0,0x40,0x00,

/*��   CB5C8 */
0x20,0x3E,0x28,0x45,0x85,0x3F,0x01,0xFF,0x00,0x00,0x7F,0x04,0x02,0x02,0x00,0x00,
0x80,0xFC,0xA0,0x10,0x10,0xF8,0x00,0xFE,0x20,0x20,0xFC,0x20,0x20,0x20,0xA0,0x40,

/*��   CBCB6 */
0x10,0x13,0x20,0x24,0x44,0xF8,0x10,0x21,0x7D,0x41,0x02,0x1A,0xE4,0x08,0x11,0x06,
0x00,0xF8,0x88,0x88,0x90,0x90,0xBE,0x44,0x44,0x48,0x28,0x10,0x30,0x48,0x8E,0x04,

/*��   CB0B4 */
0x10,0x10,0x10,0x13,0xFE,0x10,0x14,0x1B,0x30,0xD1,0x11,0x10,0x10,0x11,0x56,0x20,
0x40,0x20,0x20,0xFE,0x04,0x40,0x40,0xFE,0x88,0x10,0x90,0x60,0x58,0x8E,0x04,0x00,

/*��   CBFAA */
0x00,0x7F,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x08,0x08,0x10,0x20,0x40,0x00,
0x00,0xFE,0x20,0x20,0x20,0x20,0xFE,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,

/*ʼ   CCABC */
0x10,0x18,0x10,0x10,0xFC,0x25,0x24,0x44,0x44,0x28,0x18,0x14,0x22,0x42,0x80,0x00,
0x20,0x30,0x20,0x48,0x84,0xFE,0x84,0x00,0xFC,0x84,0x84,0x84,0x84,0xFC,0x84,0x00,

/*̫   CCCAB */
0x01,0x01,0x01,0x01,0x7F,0x01,0x01,0x01,0x02,0x02,0x04,0x05,0x08,0x10,0x20,0x40,
0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x98,0xCC,0x86,0x04,

/*��   CB0F4 */
0x20,0x20,0x27,0x20,0xFB,0x20,0x77,0x69,0xA2,0xAD,0x20,0x27,0x20,0x20,0x20,0x20,
0x40,0x40,0xFC,0x40,0xF8,0x80,0xFE,0x20,0x58,0xF6,0x40,0xFC,0x40,0x40,0x40,0x40,

/*��   CC1CB */
0x00,0x7F,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x05,0x02,
0x00,0xFC,0x18,0x60,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*��   CA3A1 */
0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};


/////////////////////////�ײ����С����/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//��ʱ��΢��
void delay(void)
{
 uchar i=0;
 i++;
 i++;
 }
//��״̬λ0��1��sta0=1:ָ���д״̬׼���ã�sta1=1:���ݶ�д״̬׼���� 
void ST01Read(void)
{
  
	PORTD=0XFF;
	while(1){
		PCD=1;		
		PRD=0;    	
	   	PRD=1;		
		if ((PORTD^0==1)&&(PORTD^1==1))  break;  //�ж�ָ����ݶ�д״̬�Ƿ�׼����
	
	}
}

//��״̬λsta2,    ��������Զ� �� ״̬�Ƿ�׼���� 
static void ST2Read(void)
{
  
	PORTD=0XFF;
	while(1){
		PCD=1;		 
		PRD=0;    	
		PRD=1;						 
		if (PORTD^2==1)  break;  
	}
}

//��״̬λsta3,    sta3=1:�����Զ� д ״̬׼���� 
static void ST3Read(void){
  
	PORTD=0XFF;
	while(1)
	{
		PCD=1;		
		PRD=0;    	
		PRD=1;		
		if (PORTD^3==1)  break; 
	}
}

//��״̬λsta6,   �������������������״̬��sta6=1:����sta6=0:��ȷ 
static void ST6Read(void)
{
  
	PORTD=0XFF;
	while(1)
	{
		PCD=1;		
		PRD=0;    	
		PRD=1;			
		if (PORTD^6==0)  break;  
	}
}

//////////////////////////////////��T6963C���ж�д����/////////////////////////////////

//д����
static void WRData(uchar DData)
{
	ST01Read();
	PCD=0;      		
	PORTD=DData;
	PWR=0;
	PWR=1;      		
} 

///������
static void RDData(void)
{
	ST01Read();             
	PCD=0;          		
	PRD=0;           		
	PRD=1;          	
}

//д����
static void WRCommand(uchar command)
{
	ST01Read();	        
	PCD=1;           
	PWR=0;	        	
	PORTD=command;      
	PWR=1;		
}

//������ָ��
static void WRCommandOne(uchar data1,uchar command)
{
	WRData(data1);		//д����
	WRCommand(command);	//д����
}
//˫����ָ��
static void WRCommandTwo(uchar data1,uchar data2,uchar command)
{
	WRData(data1);		//д����
	WRData(data2);		//д����
	WRCommand(command);	//д����
}

////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////T6963C���ô������/////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

//��ʼ��T6963 LCD ��ʾ
void Init_LCD_Graphic(void)
{
	
	//�����ı���ʾ�׵�ַ
	
	WRCommandTwo(0x00,0x00,0x40);
	
	//�����ı���ʾ����� 40�ֽ�
    
	WRCommandTwo(0x10,0x00,0x41);
	
	//����ͼ����ʾ���׵�ַ
	
	WRCommandTwo(0x00,0x10,0x42);	 	//�׵�ַ0x0800
	
	//����ͼ����ʾ�����
	
	WRCommandTwo(0x10,0x00,0x43);	//40�ֽ�

    //����CGRAM���׵�ַ

	WRCommandTwo(0x03,0x00,0x22);		
		
	//������ʾ��ʽ	
		
	WRCommand(0x80);	 	//�����ڲ��ַ�����������ʾ��ʽ���ı���ͼ���߼���
	
	//������ʾ״̬	
			
	WRCommand(0x9f);	//���ù����˸�������ʾ���ı���ʾ��ͼ����ʾ
   
}

//����ʾRAM
void ClrGraphic(void){
    uint i;
	//������ʾ��ַ
			
	WRCommandTwo(0x00,0x00,0x24);
	
	//�����Զ�д��ʽ
	
	WRCommand(0xb0);	
	//��8KRAM	
	
   	for(i=0;i<256;i++){
   	
   		WRData(0x00);
   	}   	
   	//�˳��Զ�д��ʽ
   	
	WRCommand(0xb2);
}

/////////////////////////////////////////////////////////////////////////
//***********************************************************************
//= ����ԭ��: void char_addr_Pointer_Set(uchar x, uchar y)
//= ��    ��: �����ַ�����������vram��ַ
//= ��    ��: x�����꣬y������
//= �� �� ֵ:
//= �������ʣ�˽�к���
//***********************************************************************

void char_addr_Pointer_Set(uchar x, uchar y)
{
    uint iPos;
	uint temp;
    iPos = y * 16 + x + txthome;
	temp=iPos;
	y=iPos>>8;
	x=temp&0x00ff;
    WRCommandTwo(x,y,0x24);
} 

//************************************************************************
//= ����ԭ��: void image_addr_Pointer_Set(uchar x, uchar y)
//= ��    ��: ���ݵ���������ͼ���ֽڵĵ�ַ
//= ��    ��:
//= �� �� ֵ:
//= �������ʣ�˽�к���
//************************************************************************
void image_addr_Pointer_Set(uchar x, uchar y)
{ 
    uint iPos;
	uint temp;
    iPos =y * 16 + x + grshome;
	temp=iPos;
	x=iPos>>8;
	y=temp&0x00ff;
    WRCommandTwo(y,x,0x24);
}

//**************************************************************************
//= ����ԭ��: void Point(uchar x,uchar y, bit Mode)
//= ��    ��: ��ָ������λ����ʾһ����
//= ��    ��: ����,��ʾ��������				
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= Mode 1:��ʾ 0:����õ�
//**************************************************************************
void Point(uchar x,uchar y, bit Mode)
{
    uint Address;
	uint temp;
    uchar dat;
    Address=(uint)y*16 + (x>>3) + grshome;	  //��ַת��
    dat=0xF0+7-x%8;        //����λ��������������
    if(Mode) dat=dat|0x08;
	temp=Address;
	x=Address>>8;
	y=temp&0x00ff;
	WRCommandTwo(y,x,0x24);  //���øõ����ڵ�Ԫ��ַ
    WRCommand(dat);         // ����λ���������
}

//*****************************************************************************
//= ����ԭ��: void char_wr(uchar x,uchar y, uchar *p,uchar dataa,uchar n)
//= ��    ��: ����д��һ�������ַ�
//= ��    ��: ����,Ҫ��ʾ���ַ����飬��ʾ�ĵ����ַ���Ҫ��ʾ���ַ�����				
//= �� �� ֵ:
//= �������ʣ�˽�к���
//��n=0һ����д��һ���ַ�������һ����д�����ַ�
//*****************************************************************************

void char_wr(uchar x,uchar y, uchar *p,uchar dataa,uchar n)
{
    uchar i;
  	char_addr_Pointer_Set(x,y);	//д���ַ
	if(n==0)
	  WRCommandOne(dataa,0xc0);	  //һ��д������
  	else
	  {
	    WRCommand(0xb0);//�����Զ�д
  		for(i=0;i<n;i++)
		  WRData(p[i]);	 
		  WRCommand(0xb2);   //�˳��Զ�д
	  }
}


//******************************************************************************
//= ����ԭ��: void hanzhi(uchar x,uchar y, uchar m,uchar n)
//= ��    ��: ����д��һ����������
//= ��    ��: ����,Ҫ��ʾ�ĵ�һ�����ֵ�λ�ã�������ʾ���ֵĸ�����				
//= �� �� ֵ:
//= �������ʣ�˽�к���
//��n=1һ����д��һ���ַ�������һ����д�����ַ�
//*****************************************************************************

void hanzhi(uchar x,uchar y, uchar m,uchar n)
{
    uchar i;
    uchar CGRam;
	CGRam=0x80+4*m;	 //��m���ַ�
	for(i=0;i<n;i++)
	{
	  char_addr_Pointer_Set(x,y); //�������Ͻ�д��
	  WRCommandOne(CGRam,0xc0);	  //һ��д������;
	  CGRam++;
	  y++;
	  char_addr_Pointer_Set(x,y); //�������½�д��
	  WRCommandOne(CGRam,0xc0);
	  CGRam++;
	  x++;
	  y--;
	  char_addr_Pointer_Set(x,y); //�������Ͻ�д��
	  WRCommandOne(CGRam,0xc0);
	  CGRam++;
	  y++;
	  char_addr_Pointer_Set(x,y); //�������½�д��
	  WRCommandOne(CGRam,0xc0);
	  CGRam++;
	  x++;
	  y--;
	  if(x==16)
	  {
	    x=0;		//д��һ�У��ӵڶ��п�ʼ
		y++;
		y++;
	  }
	}
}

//******************************************************************************
//= ����ԭ��: void fill_CGRAM(uchar *p,uchar m,uinit n)
//= ��    ��: ���CGRAM����
//= ��    ��: �ַ����飬д���m�����֣�ѭ��д��ĺ��ָ���
//= �� �� ֵ:
//= �������ʣ�˽�к���
//*//**************************************************************************

void fill_CGRAM(uchar *p,uchar m,uint n)
{
  uchar xx;
  uchar yy;
  uint i;
  uint ADCGram;
  uint temp;
  ADCGram=0x1c00+32*m;	//ȷ��CGRAM��ַ
  temp=ADCGram;
  xx=ADCGram>>8;
  yy=temp&0x00ff;
  WRCommandTwo(yy,xx,0x24);

  n=n*32;
  WRCommand(0xb0);
  for(i=0;i<n;i++)
	WRData(p[i]);
  WRCommand(0xb2);   //�˳��Զ�д
}

//*******************************************************************************
//= ����ԭ��: void Wr_line(uchar type,uchar x1,uchar y1, uchar Long,uchar mode)
//= ��    ��: ��һ�����߻�һ������
//= ��    ��: type=1Ϊ���ߣ�����Ϊ���ߣ�(x1,y1)Ϊ��ʼ�㣬LongΪ���ȣ�mode=1Ϊ��ʾ				
//= �� �� ֵ:
//= �������ʣ����к���
//*******************************************************************************  

void Wr_line(uchar type,uchar x1,uchar y1, uchar Long,uchar mode){
 uchar i;
if(type==1)
 {
   for(i=0;i<Long;i++)	 //������
	{ 
	   if(mode==1)
		  Point(x1+i,y1,1);
	   else  
		  Point(x1+i,y1,0);
	 }
	 return;
  }
  
else
 {
    for(i=0;i<Long;i++)		//������
	{ 
	   if(mode==1)
		  Point(x1,y1+i,1);
	   else  
		  Point(x1,y1+i,0);
	}
	 return; 
  }
}

//*****************************************************************************
//= ����ԭ��: void Show_Image(uchar x1,uchar y1,uchar x2,uchar y2,bit mode)
//= ��    ��: �������x1,y1) (x2,y2)
//= ��    ��: (x1,y1)Ϊ��ʼ�㣬��x2,y2)Ϊ�յ�  mode=1��ʾ				
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= ע    �⣺�Ե�Ϊ��λ
//*****************************************************************************  	 

void Show_Image(uchar x1,uchar y1,uchar x2,uchar y2,bit mode)
{
  char temp=x1;
  if(mode)   
   {
	 for(;y1<=y2;y1++)
	   for(x1=temp;x1<=x2;x1++)
	     Point(x1,y1,1);
   }
   else
   {
	 for(;y1<=y2;y1++)
	   for(x1=temp;x1<=x2;x1++)
	     Point(x1,y1,0);
   }
}

//**********************************************************************************
//= ����ԭ��: void image(uchar x1,uchar y1,uchar x2,uchar y2,uchar *p,bit mode)
//= ��    ��: ���趨����������д�����ֽڣ���ͼ����ʾ��
//= ��    ��: (x1,y1)Ϊ��ʼ�㣬��x2,y2)Ϊ�յ�  *poΪͼ�����飬mode=1��ʾ mode=0���			
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= ������������p=0,mode=1ʱ����������0xff,�������ã���p=0,mode=0ʱ����������0x00,�� 
//=            ����������,��p!=0ʱ��������ͼ���ã���ʱmode��Ч
//= ע    �⣺���������ݷ�Χ
//**********************************************************************************  
void image(uchar x1,uchar y1,uchar x2,uchar y2,uchar *p,bit mode)
{
   uchar temp=x1;
   uint i=0;
   for(;y1<=y2;y1++)
   {
    x1=temp;	 
    image_addr_Pointer_Set(x1,y1);	//д���ַ
	WRCommand(0xb0); //�����Զ�д
	for(;x1<=x2;x1++)
	{
	  if(p==0&&mode==1)
	  {
	     WRData(0xff);
	  }
	  else if(p==0&&mode==0)
	  {
	     WRData(0x00);
	  }
	  else 
	  {
	     WRData(p[i]);
	     i++;		 //��һ���ֽ�
	  }
	}
    WRCommand(0xb2);   //�˳��Զ�д 
    }
}

//******************************************************************************
//= ����ԭ��: void negShow(uchar x1,uchar y1,uchar x2,uchar y2,bit mode)
//= ��    ��: ��������x1,y1) (x2,y2)
//= ��    ��: (x1,y1)Ϊ��ʼ�㣬��x2,y2)Ϊ�յ�  mode=1����				
//= �� �� ֵ:
//= �������ʣ�˽�к���
//= ע    �⣺���ֽ�Ϊ��λ
//******************************************************************************  	 
void negShow(uchar x1,uchar y1,uchar x2,uchar y2,bit mode)
{
   if(mode)
   {
     WRCommand(0x81);	 	//�����ڲ��ַ�����������ʾ��ʽ���ı���ͼ���߼����
  	 image(x1,y1,x2,y2,0,1);

	}
   else
    {
	  WRCommand(0x80);	 	//�����ڲ��ַ�����������ʾ��ʽ���ı���ͼ���߼���
	  image(x1,y1,x2,y2,0,0);
	 }
}

//******************************************************************************
//= ����ԭ��: void Show_num(uchar x1,uchar y1,uchar num)
//= ��    ��: ���趨��λ����ʾһ������
//= ��    ��: (x1,y1)Ϊλ�ã�numΪ����			
//= �� �� ֵ:
//= �������ʣ����к���
//= ע    �⣺���ֽ�Ϊ��λ
//*****************************************************************************  
void Show_num(uchar x1,uchar y1,uchar num)
{
   uchar number[10]={0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};
   char_addr_Pointer_Set(x1,y1);
   WRCommandOne(number[num],0xc0);	  //һ��д������
}

///////////////////////////��ʼ��LCD////////////////////////////////////////////
void Init_LCD()
{
   Init_LCD_Graphic();
   ClrGraphic();
   fill_CGRAM(CCTable,0,22);	 //������д��CGRAM
}


#include"reg51.h"
#include"intrins.h"
#include"lcd.h"

#define uchar unsigned char
#define uint  unsigned int

sbit P20=P2^0;
sbit P21=P2^1;

uchar flag=0;/***�ߵ͵�ƽ��־***/
bit direction=0;/***�����־***/
static uchar constant=5;//���Ըı�ռ�ձ�

/****��������****/
void delay(uchar i);
void reverse(void);


/***��ʱ��t0***/
void time0(void) interrupt 1 using 1
{	
   static uchar i;
	i++;
 	/**Ƶ��Ϊ�̶���1kHZ���ң�ֻ��ռ�ձȷ����仯**/
	if(i<=constant)
		flag=1;
	if(i<=10&&i>constant)
		flag=2;		
	if(i==10) 
		i=0;
	TH0=0xff;
	TL0=0xe7;
}

/****�ı�ת���־*****/
void int1_srv (void) interrupt 2 using 2
{
	if(INT1==0)
	{
		while(!INT1);
		 direction=!direction;
	}
}

/*******�жϣ�����ռ�ձ�********/
void change(void) interrupt 0 using 0
{
	if(INT0==0)
	{
		while(!INT0);
	 	constant++;
		/***************************/
		  LCD_Write(0,LCD_CLEAR_SCREEN);
		  GotoXY(0,0);
          delay(10);
	      Print(" Duty cycle ! ");
		  GotoXY(5,1);
          delay(10);
		  if(constant==10)
		  {
		  	LCD_Write(LCD_DATA,0+'0');
		   }
	 	  else
          	LCD_Write(LCD_DATA,constant+'0');	
	  
		  delay(10);
		  Print(":");
		  delay(10);

		  if(constant!=10)
		  	LCD_Write(LCD_DATA,10-constant+'0');
		  else
		   { LCD_Write(LCD_DATA,1+'0');
			 delay(10);
			 LCD_Write(LCD_DATA,0+'0');
			}
		/********************************/
		if(constant==10)
		constant=0;
	}
}

/****��ʱ****/
void delay(uchar i)
{
	while(i--)
	_nop_();
}

/*************************/

void main()
{	
	EA=1;
	TMOD=0x01;
	ET0=1;
	TR0=1;

	EX0=1;
	IT0=1;

	EX1=1;
	IT1=1;

	TH0=0xff;
	TL0=0xe7;
	/************/
	LCD_Initial();
	delay(10);
	GotoXY(0,0);
	delay(10);
	Print(" Duty cycle(5:5)! ");
	GotoXY(0,1);
	delay(10);
	Print(" please press !");
	/*************/
	while(1)
	{
		reverse();
	}
}

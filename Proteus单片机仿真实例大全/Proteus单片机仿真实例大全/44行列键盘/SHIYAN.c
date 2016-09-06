#include"reg51.h"
#include"LCD1602.h"

#include"hardware.h"

char code tab[4][4]={		{'1','4','7','#'},
                  			{'2','5','8','0'},
                  			{'3','6','9','*'},
                  			{'A','B','C','D'}};       //0µΩFµƒ16∏ˆº¸÷≤

void delay(unsigned char a)
	{
	unsigned char i;
	while(a--)
		for(i=100;i>0;i--)
			;
	}

char kbscan()          //º¸≈Ã…®√Ë
	{
 	unsigned char hang,lie,key;
	if(P3!=0x0f)
	delay(5);
	if(P3!=0x0f)
		{
		switch(P3&0x0f)
				{
				case 0x0e:lie=0;break;
				case 0x0d:lie=1;break;
				case 0x0b:lie=2;break;
				case 7:lie=3;break;
				}
		P3=0xf0;
		P3=0xf0;
		switch(P3&0xf0)
				{
				case 0xe0:hang=0;break;
				case 0xd0:hang=1;break;
				case 0xb0:hang=2;break;
				case 0x70:hang=3;break;
				}
		P3=0x0f;
		while(P3!=0x0f);
		key=tab[hang][lie];
		}
	else
		key=0;
	return (key);
	}

void main()
	{
	unsigned char temp;
	LCD_initial();
	LCD_prints("piaoling");
	P3=0x0f;
	P0=0xff;
	while(1)
		{
		temp=kbscan();
		if(temp!=0)
			{
			P0=temp;
			LCD_set_position(0x40);
			LCD_printc(temp);
			}
		}
	}




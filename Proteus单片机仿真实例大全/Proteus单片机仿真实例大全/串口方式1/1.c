#include <reg51.h>

//字形码****按列取模
char code table[]={
			0x5E,0x22,0x52,0xAC,0x7E,0xA1,0x52,0xBF,	//‘飘’
			0x7E,0xA8,0xD2,0xA5,0x5E,0x22,0x00,0x04,
			0x7F,0xF8,0x46,0x60,0x41,0x80,0x46,0x60,
			0xFF,0xFC,0x40,0x02,0x00,0x0E,0x00,0x00,
			0x08,0x20,0x30,0x20,0x20,0x40,0x0AA,0x40,	//‘零’
			0xAA,0x90,0xAA,0x90,0xA1,0x54,0xFE,0x32,
			0xA1,0x15,0xAA,0x98,0xAA,0x90,0xAA,0x40,
			0x20,0x40,0x28,0x20,0x30,0x20,0x00,0x00,
			0x02,0x00,0x06,0x00,0x7A,0xFC,0x12,0x80,	//‘制’
			0x12,0x80,0xFF,0xFF,0x12,0x88,0x32,0x84,
			0x16,0xF8,0x02,0x00,0x1F,0xE0,0x00,0x02,
			0x00,0x01,0xFF,0xFE,0x00,0x00,0x00,0x00,
			0x01,0x00,0x02,0x00,0x04,0x00,0x1F,0xFF,	//‘作’
			0xE1,0x00,0x02,0x00,0x0C,0x00,0xF0,0x00,
			0x1F,0xFF,0x11,0x10,0x11,0x10,0x13,0x10,
			0x11,0x30,0x30,0x10,0x10,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//'!'
			0x00,0x00,0x00,0x00,0x38,0x00,0x7F,0xCC,
			0x7F,0xCC,0x38,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//显示空屏，如果只有一个字或将字全部移出必须设置一个空屏幕
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
			};

void delay(int c)
	{
	int i,j;
	for(i=0;i<c;i++)
		for(j=0;j<10;j++)
			;
	 }

void main()
	{
	unsigned char i,j,k;	//i:每个字的显示循环；j每个字的显示码除以2；k每列刷新次数
	unsigned char b=0;		//显示偏移控制，char类型最多只能显示14个汉字+一个空白位字符
	unsigned char a;		//控制移动间隔时间
while(1)
	{
	j=0;
	if(a>5)	//移动间隔时间；取值0--255
		{
		a=0;
		b+=2;
		if(b>=160)	//显示到最后一个字，回头显示，判断值=字数*32
			{
			b=0;
			}	
		}
	for(i=0;i<16;i++)
		{
		P1=i;
		for(k=0;k<5;k++)
			{
			P0=table[j+b];
			P2=table[j+b+1];
			delay(2);
			P0=0x00;
			P2=0x00;
			}
		j+=2;
		}
	   	a++;
	}
}


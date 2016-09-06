/////////////////////////////////////////////////
/////加减记数器源程序counter.c
/////
/////////////////////////////////////////////////


#include "stdio.h"
#include "reg51.h"


// 共阳 0 - 9 的编码 12MHz
unsigned char code table[] = { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF };
//第1-- 6 位的片选线
unsigned char code dig[]   = { 0x21,0x11,0x09,0x05,0x03,0x08};//= { 0x80,0x03,0x05,0x09,0x11,0x21};
                           
unsigned char buffer[8];
unsigned char scan,i,ch,KeyVal;
bit           fKey,Key1,Key2,Key3,OldKey1,OldKey2,OldKey3,fBI;

unsigned long int counter,tmp;


void counter_display(void)
{
	buffer[5]=counter/100000;
	buffer[4]=counter/10000-buffer[5]*10;
	buffer[3]=counter/1000 -buffer[5]*100   -buffer[4]*10;
	buffer[2]=counter/100  -buffer[5]*1000  -buffer[4]*100  -buffer[3]*10;
	buffer[1]=counter/10   -buffer[5]*10000 -buffer[4]*1000 -buffer[3]*100 -buffer[2]*10;
	buffer[0]=counter/1    -buffer[5]*100000-buffer[4]*10000-buffer[3]*1000-buffer[2]*100-buffer[1]*10;

}
void delay(void)
{
	int i;
	for(i=0;i<500;i++)
	{
		;
	}
}

void main(void)
{
	unsigned int i;
	
	P3=dig[1];
	P1=table[1];
	TCON &= 0xCF;               // 初始化Timer0
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0   = 0xff;           
	TH0   = 0xff;
	EA    = 1;
	ET0   = 1;
	TR0   = 1;
	counter=0;
	while(1){
		for(i=0;i<1;i++){
		delay();
		}
	    counter++;		
	}
}


void timerint () interrupt 1 
{
		unsigned int i,j;
		unsigned char n;
		EA=0;
		
	
        counter_display();
		for(i=0,n=0;i<=5;i++){
			if(buffer[5-i]!=0){
				n=5-i;
				break;
			}
	
		}
		for(j=0;j<5;j++){
			for(i=0;i<=n;i++){
				P3=dig[i];
			    P1=table[buffer[i]];
				delay();
			}
		}
		EA=1;
        TL0 = -2500%256;
        TH0 = -2500/256;                     //2.5ms定时
        TR0 = 1;
}

//调试程序成功，只是不知什么原因，显示不正常
//预期目的：按键显示键值

#include<reg51.h>
#include<stdio.h>
#include<absacc.h>


#define unchar unsigned char 
#define unint unsigned int

unchar code LEDSEG[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                        0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
unchar temp,i,j;
unchar dis_buf[]={16,16,16,0};		  //显示3个空格和一个0
void display(void);
void keyscan(void);
unchar testkey(unchar); 
void delay(void);
//===============================================================================
void main(void)
{IT0=1;						  //外部中断0初始化
 EX0=1;
 EA=1;
 P2=0xff;
 P0=0xff;
 while(1)
	{display();}
}

//********************************************************************************
void key_int(void) interrupt 0
{
 unchar temp_h,temp_l,keynum;          //行码 列码 键值
 unchar code_h,code_l;
 if(testkey(0xf0))
   	{
	 temp_l=0;
	 temp_h=0;						  //功能：扫描键盘并更新显示缓冲区
     code_l=0xfe;
     while(temp_l<0x04)
	    {
		 if(testkey(code_l)==1)
		   {
		    code_h=P2;			
		  	if(P2^4==0) temp_h=0x00;
		  	else if(P2^5==0)temp_h=0x04;
		    else if(P2^6==0)temp_h=0x08;
		   	else temp_h=0x0c;
		 	while(testkey(0xf0)){;} 	 //等待按键放开
			break;
		   }
		 else{code_l=code_l<<1|0x01;
	    	  temp_l++;
			 }
    	}	
     keynum=temp_h+temp_l;	         //更新显示缓冲区
     dis_buf[0]=dis_buf[1];
	 dis_buf[1]=dis_buf[2];
	 dis_buf[2]=dis_buf[3];
	 dis_buf[3]=keynum;
	}
}
	

//----------------------------------------
unchar testkey(unchar scan_code )   //测试是否有键按下，scan_code是扫描码，返回1说明有键按下
{
  unchar temp;
  P2=scan_code;
  delay();            //延时1ms防抖   ／／1ms不够，最好是20ms !!!!!!!!!!!!!!!!!
  temp=P2;
  if((~temp)&0xf0)  return (1);
	else   return (0);
} 

//********************************************************************************
void display(void)			    //显示4位数
{
 unchar i,disbit;
 disbit=0xfe;
 
 for(i=0;i<4;i++)
	{
	//P0=LEDSEG[dis_buf[i]];
     P2=disbit;		            //选中要显示的管
	 P0=LEDSEG[dis_buf[i]];	   //要先选中，才能输出显示数据！！！！！！！！！！！
	 delay();
	 disbit=disbit<<1;			  //改变位码
     disbit++;
	 }
	
}
//================================================================================
/*void delay(void)                //
{EA=1;
ET0=1;
TMOD=0x01;
TH0=0xFC;
TL0=0x18;
TR0=1;
while(!TF0);
TF0=0;
}	*/

void delay(void)  // 延时1ms
{
  int a=0;
  for(a=0;a<1000;a++);
 }

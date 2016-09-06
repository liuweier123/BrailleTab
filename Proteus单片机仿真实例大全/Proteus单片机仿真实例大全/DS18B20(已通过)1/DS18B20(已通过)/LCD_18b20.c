//#include <at89x51.h>//用AT89C51时就用这个头文件
#include <reg52.h>//用华邦W78E58B时必须用这个头文件
//#include <absacc.h>
//#include <ctype.h>
//#include <math.h>
//#include <stdio.h>
//#include <string.h>
#include <DS18B20.h>			//测温头文件
#include <LCD1602.h>			//液晶显示头文件
#include <keyscan.h>			//键盘扫描头文件
sbit alarm=P2^6;					//报警信号
//sbit DQ = P3^7;					//定义DQ引脚为P3.7
unsigned char key_value;            //存放键盘扫描值
bit up_one,down_one; 				//加1和减1标志
bit alarm_up_flag,alarm_down_flag;	//上限报警和下限报警设置标志
bit set_temper_flag;				//设置控制标志温度标志
bit alarm_switch;					//报警开关

unsigned char user_temper;			 //用户标定温度	
unsigned char TH=110,TL=-20,RS=0x3f; //上限温度110,下限-20,分辨率10位,也就是0.25C
unsigned char t[2],*pt;				//用来存放温度值,测温程序就是通过这个数组与主函数通信的
unsigned char  TempBuffer1[17]={0x2b,0x20,0x30,0x30,0x2e,0x30,0x30,0x20,
								0x53,0x45,0x54,0x2b,0x20,0x30,0x30,0x43,'\0'};
								//显示实时温度,上电时显示+ 00.00 SET+ 00C
unsigned char  TempBuffer0[17]={0x54,0x48,0x3a,0x2b,0x20,0x30,0x30,0x20,
								0x54,0x4c,0x3a,0x2b,0x20,0x30,0x30,0x43,'\0'};
								//显示温度上下限,上电时显示TH:+ 00 TL:+ 00C							
unsigned char code dotcode[4]={0,25,50,75};
/***因显示分辨率为0.25,但小数运算比较麻烦,故采用查表的方法*******
再将表值分离出十位和个位后送到十分位和百分位********************/



/***********用户设定温度转换为LCD显示数据**************
*功能:将用户设定温度user_temper,分离出符号位,百、十、个位
	  并将它们转化为ACSII码,送到液晶显示缓冲区
******************************************************/
void user_temper_LCD(unsigned char temper)
{
	if(temper>0x7f)				//判断正负,如果为负温,将其转化为其绝对值
	{
		TempBuffer1[11]=0x2d;	//0x2d为"-"的ASCII码
		temper=~temper;			//将负数的补码转换成绝对值
		temper++;
	}
	else TempBuffer1[11]=0x2b;	////0x2B为"+"的ASCII码
	TempBuffer1[12]=temper/100+0x30;		             //分离出temper的百十个位
  	if( TempBuffer1[12]==0x30) TempBuffer1[12]=0xfe;     //百位数消隐
  	TempBuffer1[13]=(temper%100)/10+0x30;				     //分离出十位
  	TempBuffer1[14]=(temper%100)%10+0x30;	 			     //分离出个位
}



/***************温度上下限转换为LCD显示数据************
*功能:将上下限报警温度,分离出符号位,百、十、个位
	  并将它们转化为ACSII码,送到液晶显示缓冲区
******************************************************/
void alarm_LCD( unsigned char TH, unsigned char TL)	
{ 
   if(TH>0x7F)                    //判断正负,如果为负温,将其转化为其绝对值
   {
    TempBuffer0[3]=0x2d;	     //0x2d为"-"的ASCII码
	TH=~TH;						 //将负数的补码转换成绝对值
	TH++;
   }
   else TempBuffer0[3]=0x2b;	//0x2B为"+"的ASCII码

   if(TL>0x7f)
   {
   TempBuffer0[11]=0x2d;	     //0x2d为"-"的ASCII码
   TL=~TL+1;
   }
   else TempBuffer0[11]=0x2b;	//0x2B为"+"的ASCII码

  TempBuffer0[4]=TH/100+0x30;		             //分离出TH的百十个位
  if( TempBuffer0[4]==0x30) TempBuffer0[4]=0xfe; //百位数消隐
  TempBuffer0[5]=(TH%100)/10+0x30;				//分离出十位
  TempBuffer0[6]=(TH%100)%10+0x30;	 			//分离出个位
  TempBuffer0[12]=TL/100+0x30;		             //分离出TL的百十个位
  if( TempBuffer0[12]==0x30) TempBuffer0[12]=0xfe; //百位数消隐
  TempBuffer0[13]=(TL%100)/10+0x30;				//分离出十位
  TempBuffer0[14]=(TL%100)%10+0x30;	 			//分离出个位
}

/**********温度转换为LCD显示数据****************
*功能:将两个字节的温度值,分离出符号位,整数及小数
	  并将它们转化为ACSII码,送到液晶显示缓冲区
************************************************/
void temper_LCD(void)	
{
   unsigned char x=0x00,y=0x00;
   t[0]=*pt;
   pt++;
   t[1]=*pt;
   if(t[1]>0x07)                    //判断正负温度
   {
    TempBuffer1[0]=0x2d;	     //0x2d为"-"的ASCII码
	t[1]=~t[1];			 /*下面几句把负数的补码*/
	t[0]=~t[0]; 		 /* 换算成绝对值*********/
	x=t[0]+1;				 /***********************/
	t[0]=x;					 /***********************/
	if(x>255)                /**********************/
	t[1]++;				 /*********************/
   }
   else TempBuffer1[0]=0x2b;	//0xfe为变"+"的ASCII码
  t[1]<<=4;		//将高字节左移4位
  t[1]=t[1]&0x70;		//取出高字节的3个有效数字位
  x=t[0];					//将t[0]暂存到X,因为取小数部分还要用到它
  x>>=4;					//右移4位
  x=x&0x0f;					//和前面两句就是取出t[0]的高四位	
  t[1]=t[1]|x;			//将高低字节的有效值的整数部分拼成一个字节
  TempBuffer1[1]=t[1]/100+0x30;		             //+0x30 为变 0~9 ASCII码
   if( TempBuffer1[1]==0x30) TempBuffer1[1]=0xfe; //百位数消隐
  TempBuffer1[2]=(t[1]%100)/10+0x30;				//分离出十位
  TempBuffer1[3]=(t[1]%100)%10+0x30;	 			//分离出个位
  t[0]=t[0]&0x0c;							//取有效的两位小数
  t[0]>>=2;									//左移两位,以便查表
  x=t[0];										
  y=dotcode[x];									//查表换算成实际的小数
  TempBuffer1[5]=y/10+0x30;						//分离出十分位
  TempBuffer1[6]=y%10+0x30;						//分离出百分位
}			

/*********键盘命令处理函数************
*功能:把键盘值转化成相应的功能标志位
*备注:为了提高程序的健壮性,在功能标志位无效时,
**up_one和down_one都无效,并且各功能标志之间
**采用互锁处理,虽然这样麻烦,特别是功能标志较多时
**更是麻烦,但各功能标志之间是同级别的;
**也可采用多重if else方法,虽然简单,
**但各功能标志之间有了明显的优先级差别
**************************************/
void key_command(unsigned char x)			    	
{
	switch(x)
	{
		case 1: up_one=1;break;
  		case 2: down_one=1;break;
		case 5: alarm_up_flag=!alarm_up_flag;break;
		case 6: alarm_down_flag=!alarm_down_flag;break;
		case 7: set_temper_flag=!set_temper_flag;break;
		case 8: alarm_switch=!alarm_switch;break;
		default: break;
	}
	if(!(alarm_up_flag||alarm_down_flag||set_temper_flag))
	{
		up_one=0x00;		//在没有相应功能标志有效时
		down_one=0x00;		//up_one和down_one都被锁定
	}
	if(alarm_up_flag&&(!alarm_down_flag)&&(!set_temper_flag))//设置上限报警
	{
		if(up_one)//上限报警加1
		{
			TH++;up_one=0;
			if(TH>=100)//超过100度,回零到20度
			TH=20;
		}
		if(down_one)//上限报警减1
		{
			TH--;down_one=0;
			if(TH<=20)//小于20度,回零到20度
			TH=20;
		}
	}
	if((!alarm_up_flag)&&(alarm_down_flag)&&(!set_temper_flag))//设置下限报警
	{
		if(up_one)
		{
			TL++;up_one=0;
			if(TL>=20)//高于20度,回零到0度
			TL=0;
		}
		if(down_one)
		{
			TL--;down_one=0;
			if(TL<=0)//低于0度,回零到0度
			TL=0;
		}
	}
	
	if((!alarm_up_flag)&&(!alarm_down_flag)&&(set_temper_flag))//设置用户标定温度
	{
		if(up_one)
		{
			user_temper++;up_one=0;
			if(user_temper>=60)//高于60度,回零到0度
			user_temper=0;
		}
		if(down_one)
		{
			user_temper--;down_one=0;
			if(user_temper<=0)//低于0度,回零到0度
			user_temper=0;
		}			
	}
	//if(alarm_switch)
				
}


main()
{												
 setds18b20(TH,TL,RS);    				//设置上下限报警温度和分辨率
 delay(100); 					 
 while(1)
 {											
    pt=ReadTemperature();		 		 //测温函数返回这个数组的头地址
										 //读取温度,温度值存放在一个两个字节的数组中,
	temper_LCD();						 //实测温度转化为ACSII码,并送液晶显示缓冲区
	user_temper_LCD(user_temper);		 //用户设定温度转化为ACSII码,并送液晶显示缓冲区
	alarm_LCD(TH,TL);					 //上下限报警温度转化为ASCII码,并送液晶显示缓冲区
	LCD_Initial();							//第一个参数列号,第二个为行号,为0表示第一行
											//为1表示第二行,第三个参数为显示数据的首地址
	LCD_Print(0,0,TempBuffer0);	
	LCD_Print(0,1,TempBuffer1); 
		
	scan_full();                     //看有无键按下
	if(key_ok)						//如有键按下则看到底哪个键按下
	{
	key_value=key_scan();			 //调用键盘扫描程序
	key_command(key_value);			 //键盘命令处理函数
	}			
 }
}
  




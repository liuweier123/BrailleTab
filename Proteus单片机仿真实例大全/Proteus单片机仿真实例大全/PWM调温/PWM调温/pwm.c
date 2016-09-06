#include <reg52.h>
//#include <at89x52.h>
//#include <keyscan.h>
extern void scan_full(void);
extern unsigned char key_scan(void);
extern bit key_ok;
unsigned char pwm_set,key_value;
unsigned char count;
sbit PWM=P3^6;
bit up,down,set_flag;
unsigned char code BCD[]={0x3f,0x06,0x5b,0x4f, //此处是将0-F转换成相应的BCD码
                          0x66,0x6d,0x7d,0x07, 
                          0x7f,0x6f,0x77,0x7c, 
                          0x39,0x5e,0x79,0x71};
void delay1(unsigned char t)
{
 while(t--);
}



void pwm(void) interrupt 5//定时器2产生PWM波形
{
	TF2=0;					//定时器2的溢出标志要软件清除,
							//但当RCLK或TCLK为1时由硬件清除
	if((count>=pwm_set)&&(count<10))
		PWM=1;
	else	PWM=0;	
	count++;	
	if(count==10)
	count=0x00;
	
}


void key_pwm(unsigned char x)//把键值转化为PWM设置值
{
	switch(x)				//把矩阵键盘转化为独立键盘
	{
		case 1:up=1;break;
		case 2:down=1;break;
		case 3:set_flag=!set_flag;break;
		default:break;
	}
	
	if(up&&set_flag)		//设置PWM参数:pwm_set
	{
		pwm_set++;
		up=0;
		if(pwm_set>=10)
		pwm_set=0x00;
	}
	if(down&&set_flag)
	{
		pwm_set--;
		down=0;
		if(pwm_set==0xff)
		pwm_set=9;
	}
	if(!set_flag)
	{
		up=0;
		down=0;
	}
}


void main(void)
{
	TH2=0xb1;	//定时20MS
	TL2=0xe0;
	RCAP2H=0xb1;//定时器2溢出时会把这个单元的内容送到TH2和TL2中
 	RCAP2L=0xe0;
	EA=1;
	ET2=1;
	TR2=1;
	while(1)
	{
		scan_full();	//看是否有键按下
		if(key_ok)		//有键按下,则判断到底是哪个键按下
		{
			key_value=key_scan();//键值送key_value暂存
			P0=~BCD[key_value];	 /*此三句是将键值显示出来*/
  			P2=0xfe;			/**						 */
			delay1(200);		/*************************/
			key_pwm(key_value);  //调用键值转PWM设置参数函数
			key_value=0x00;		 //清除键值,以免一次按下,多次响应
		}
		P0=~BCD[pwm_set];		/***此三句是将pwm_set值显示出来*/
		P2=0xfd;				/*******					*/
		delay1(200);			/****************************/
	}
}

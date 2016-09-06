/**********************************************
功能：32x16LED汉字字幕程序
编译：ICC AVR
作者：刘伟
**********************************************/



#include <iom16v.h>
#include <macros.h>
#include <font.h>
#define LED_DATA_LOW    PORTA
#define LED_DDR_LOW     DDRA
#define LED_DATA_HIGH   PORTB
#define LED_DDR_HIGH    DDRB
#define LED_SCAN_DATA		PORTC
#define LED_SCAN_DDR		DDRC
#define uchar unsigned char 
#define uint unsigned int
//缓存大小，对应LED屏的大小
#define buffer_long	64
//定义字模数据数组的大小，即所存字的个数	 	
#define gb16_tabel_long 62
/*        利用定时器1 定时扫描LED屏   */
/*        定时参数对显示效果影响很大  */
#define T1_TIME_H 0xe7
#define T1_TIME_L 0x50

enum direction {right,left}dir_f;
uchar display_buffer[buffer_long];

/**************** LED屏初始化**************************/
void led_initial ( void )
{
 uchar i;
 	//display_buffer initial
 for (i=0; i<buffer_long; i++)
 		display_buffer[i] = 0x00;
 		
	// port initial
	LED_DDR_LOW = 0xff;
	LED_DDR_HIGH = 0xff;
	LED_SCAN_DDR = 0x1f;
	
	//移动方向 right or left
	dir_f = left;
	//t0 initial
 CLI(); //disable all interrupts
 TCCR1B = 0xe0; //stop
 TCNT1H = T1_TIME_H; //setup
 TCNT1L = T1_TIME_L;
 OCR1AH = 0x01;
 OCR1AL = 0xF4;
 OCR1BH = 0x01;
 OCR1BL = 0xF4;

 ICR1H  = 0x01;
 ICR1L  = 0xF4;
 TCCR1A = 0x00;
 TCCR1B = 0x02; //start Timer
 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x04; //timer interrupt sources
 SEI(); //re-enable interrupts
}
/*************** 字符串输出子程序***********************/

void print_char (char *p)
{
	uchar tab_n,j,i=0;
	int k;
	uchar d0,d1;
	while(p[i] > 0)
	{
		if (p[i] >=128)//如果是汉字
		{
			/*     查找 移位输出     */
			for(j=0; j<=gb16_tabel_long; j++)
			{
				if ((gb_16[j].index[0] == p[i]) && (gb_16[j].index[1] == p[i+1]))
					{
					 if ( dir_f == left )//如果字向左移动就顺序读字模			   					
						for (k=0; k<32; k++)
						{
							d0 = gb_16[j].mask[k];
							k++;
							d1 = gb_16[j].mask[k];
							move_to_buffer (d0,d1);
							delay(1);
						}
					 else //如果字向右移动就逆序读字模
					 	for (k=31; k>=0; k--)
						{
							d1 = gb_16[j].mask[k];
							k--;
							d0 = gb_16[j].mask[k];
							move_to_buffer (d0,d1);
							delay(1);
						}
					break;//找到了就退出循环
					}
			}
			/*        字库没有的字，则输出空白0x00  */
			if (j>gb16_tabel_long)//
			   for (k=0; k<16; k++)
				{
					d0 = 0x00;
					d1 = 0x00;
					move_to_buffer (d0,d1);
					delay(1);
				}
			i+=2;
 	  }
 	 	else	 		 			 //如果是字符
 	 	{
 	 		j = p[i]-32;
			if (dir_f == left)
			   for (k=0; k<16; k++)
			   {
					d0 = ASC_MSK[(j*16)+k];
					k++;
					d1 = ASC_MSK[(j*16)+k];
					move_to_buffer (d0,d1);
					delay(1);
				}
			else 
				 for (k=15; k>=0; k--)
			   	 {
					d1 = ASC_MSK[(j*16)+k];
					k--;
					d0 = ASC_MSK[(j*16)+k];
					move_to_buffer (d0,d1);
					delay(1);
				 }
			i++;
 	 	}
	}
}
/******************** 数据移入缓存*********************/
// d0 移入数据高八位
// d1 移入数据低八位
void move_to_buffer (uchar d0,uchar d1)
{
	uchar i;
	if ( dir_f == right)//判断移动方向
		{
			for (i=0; i<(buffer_long-2); i++)
			{
				display_buffer[buffer_long-1-i] = display_buffer[buffer_long-1-i-2];	
			}
			display_buffer[0] = d0;
			display_buffer[1] = d1;  
		}
	else 
		{
			for (i=0; i<(buffer_long-2); i++)
			{
				display_buffer[i] = display_buffer[i+2];	
			}
			display_buffer[buffer_long-2] = d0;
			display_buffer[buffer_long-1] = d1;  
		}
}
/*********************显示数据扫描********************/
#pragma interrupt_handler scan_led:9
void scan_led (void)
{
	uchar buf_c,scan_c=0;
	TCNT1H = T1_TIME_H; //reload counter high value
  	TCNT1L = T1_TIME_L;; //reload counter low value
	for (buf_c=0; buf_c<buffer_long;)
	{
		//LED_DDR_LOW = 0xff;
	 //LED_DDR_HIGH = 0xff;
		LED_DATA_HIGH = display_buffer[buf_c];
		buf_c++;
		LED_DATA_LOW = display_buffer[buf_c];
		buf_c++;
		LED_SCAN_DATA = scan_c;
	    delay(8);
		//LED_DDR_LOW = 0x00;
		//LED_DDR_HIGH = 0x00;
		scan_c++;
	}
}

/**********************延时子程序*********************/
void delay (uchar d_time)
{
	uchar i,j;
	for (i=0; i<=d_time; i++)
	{
		j=25;
		while(j--);
	} 
}
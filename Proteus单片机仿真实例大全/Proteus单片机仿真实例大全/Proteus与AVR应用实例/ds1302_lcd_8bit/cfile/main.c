#include "includes.h"
#define MAIN_C
unsigned char alarm_1_set, alarm_2_set, alarm_3_set;
//unsigned char b10;
//unsigned char bpm;

/**************************************************************************************/
//函数名	    ：main
//属性		：私有
//功能		：主函数
//输入参数	：
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
void main(void)
{
	unsigned char hour, min, sec; 
	//unsigned char temp1, temp2, temp3;
	unsigned char test[] = "Nowtime is :";
	//min  = 0;
	//sec  = 0;
  	//hour = 0;
  	//SPL = 0x5f;
	//init_usart();
	initgraph();
	write_byte(w_protect,0x00);  //make sure that the WP bit is cleared
	//set time
	write_byte(sec_w,0x09);			
	write_byte(min_w,0x09);
	write_byte(hour_w,0x09);	
	while (1)
	{                   	
		//temp1 = sec;
	        //temp2 = min; 
		//temp3 = hour;
		sec  = read_byte(sec_r);		//read the seconds		
		min  = read_byte(min_r);		//read the minites
		hour = read_byte(hour_r);	//read the minites	
		gotoxy(0,0);
		outtext(test);		
		gotoxy(0,1);
		delay_nms(10);
		put_char('0'+hour/10);
		put_char('0'+hour%10);
		put_char(':');
		put_char('0'+min/10);
		put_char('0'+min%10);
		put_char(':');
		put_char('0'+sec/10);
		put_char('0'+sec%10);
	}
}


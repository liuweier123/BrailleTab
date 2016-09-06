//#define 1302_TEST_C
#include "includes.h"

//unsigned char b10;
//unsigned char bpm;

#define WDR()  asm("wdr")
unsigned char alarm_1_set, alarm_2_set, alarm_3_set;
__flash unsigned char test[] = "DS1302 time is :";


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
void  main(void)
{
    unsigned char hour, min, sec; 
    unsigned char date,month;
    unsigned char flag;
    flag = 1;
    PORTB = 0x00;
    DDRB = 0x00;
    DDRD = 0x7f;
    PORTD = 0xFF;
    //n = sprintf(tst,"%f",show);
    Init_LCD();
    LCD_DisplayString(0,1,"Initialize OK!");
    delay_nms(500);
    LCD_WriteControl (LCD_CLEAR);
    WDR();
    write_byte(w_protect,0x00);  //make sure that the WP bit is cleared
    //set time    
    //write_byte(sec_w,0x09);			
    //write_byte(min_w,0x09);
    //write_byte(hour_w,0x09);
    while (1)
    {     	
        sec    = read_byte(sec_r);	//read the seconds		
	min    = read_byte(min_r);	//read the minites
	hour   = read_byte(hour_r);	//read the minites	
	month  = read_byte(month_r);
	date   = read_byte(date_r); 		
	WDR();		
	LCD_DisplayString_F(1,1,test);
	
	if (flag)
	{
	    LCD_Cursor(2,1);
	    //delay_nms(10);
	    LCD_DisplayCharacter('0'+hour/10);
	    LCD_DisplayCharacter('0'+hour%10);
	    LCD_DisplayCharacter(':');
	    WDR();
	    LCD_DisplayCharacter('0'+min/10);
	    LCD_DisplayCharacter('0'+min%10);
	    LCD_DisplayCharacter(':');
	    WDR();
	    LCD_DisplayCharacter('0'+sec/10);
	    LCD_DisplayCharacter('0'+sec%10);
	    LCD_Cursor(2,11);
	    WDR();
	    LCD_DisplayCharacter('0'+month/10);
	    LCD_DisplayCharacter('0'+month%10);
	    LCD_DisplayCharacter('/');
	    WDR();
	    LCD_DisplayCharacter('0'+date/10);
	    LCD_DisplayCharacter('0'+date%10);	
	    WDR();	
	}			
    }
}


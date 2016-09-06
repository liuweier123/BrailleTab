#include "includes.h"
#define DS1302_C

 unsigned char b10;
 unsigned char bpm;
/**************************************************************************************/
//函数名	：get_hours
//属性		：私有
//功能		：获得小时
//输入参数	：无
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
unsigned char get_hours(void)
{

	unsigned char i;
	unsigned char R_Byte;
	unsigned char TmpByte;

	reset();
	write(0x85);
	ddr_set_io();
	R_Byte = 0x00;
	prt_clear_io();

	ddr_clear_io();

	for(i = 0; i < 4; i++) //get the first 4 bits
	{
                TmpByte = 0;
                if((pinp&(1<<io)))
                        TmpByte = 1;
		TmpByte <<= 7;
		R_Byte >>= 1;
		R_Byte |= TmpByte;

		prt_set_clk();
		delay_nus(2);
		prt_clear_clk();
		delay_nus(2);
	}

        b10 = 0;
	if((pinp&(1<<io)))
                b10 = 1;

	prt_set_clk();
	delay_nus(2);
	prt_clear_clk();
	delay_nus(2);

        bpm = 0;
	if((pinp&(1<<io)))
                bpm = 1;

	prt_set_clk() ;
	delay_nus(2);
	prt_clear_clk();
	delay_nus(2);

	prt_clear_rst();
	prt_clear_clk();

	R_Byte	>>= 4;
	return R_Byte;
}
/**************************************************************************************/
//函数名	：readbyte
//属性		：私有
//功能		： 
//输入参数	：
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/

unsigned char read_byte(unsigned char w_byte)	//read the byte with register w_byte
{
	unsigned char temp;
	reset();
	write(w_byte);
	temp = read();
	prt_clear_rst();
	prt_clear_clk();
	return temp;
}
/**************************************************************************************/
//函数名	：write_byte
//属性		：私有
//功能		： 
//输入参数	： 
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
void write_byte(unsigned char w_byte, unsigned char w_2_byte)	//read the byte with register w_byte
{
	reset();
	write(w_byte);
	write(w_2_byte);
	prt_clear_rst();
	prt_clear_clk();
}
/**************************************************************************************/
//函数名	：reset
//属性		：私有
//功能		： 
//输入参数	： 
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
void reset(void)		//sets the pins to begin and end the ds1302 communication
{
	ddr_set_rst();
	prt_clear_clk();
	prt_clear_rst();
	prt_set_rst();
}
/**************************************************************************************/
//函数名	：write
//属性		：私有
//功能		： 
//输入参数	： 
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
void write(unsigned char W_Byte)	//writes the W_Byte to the DS1302
{
	unsigned char i;
	DDRC = 0xFF;

	for(i = 0; i < 8; i++)
	{
		prt_clear_io();
		if(W_Byte &0x01)
		{
			prt_set_io();
		}
		prt_set_clk();
		delay_nus(1);//delay_nus(2);
		prt_clear_clk();
		delay_nus(1);//delay_nus(2);
		W_Byte >>=1;
	}
}
/**************************************************************************************/
//函数名	：LCD_DispXY
//属性		：私有
//功能		：设定显示位置
//输入参数	：posx,posy 设定的坐标  右上角为 0,0
//输出参数	：
//返回值	：
//修改日期	：
//修改人	：
/**************************************************************************************/
unsigned char read(void)		//reads the ds1302 reply
{
	unsigned char i;
	unsigned char R_Byte;
	unsigned char R_Byte2;
	unsigned char TmpByte;
	ddr_set_io();
	R_Byte =  0x00;
	R_Byte2 = 0x00;
	prt_clear_io();
	ddr_clear_io();
	for(i = 0; i < 4; i++) //get the first 4 bits
	{
                TmpByte = 0;
		if((pinp&(1<<io)))
		{
                        TmpByte = 1;
                        TmpByte = 0x80;
                }
		//TmpByte <<= 7;
		R_Byte =  (R_Byte>>1);//R_Byte >>= 1;
		R_Byte |= TmpByte;
		prt_set_clk();
		delay_nus(1);//delay_nus(2);
		prt_clear_clk();
		delay_nus(1);//delay_nus(2);
	}
	for(i = 0; i < 4; i++) //get the next 3 bits
	{
                TmpByte = 0;
		if((pinp&(1<<io)))
		{
                        TmpByte = 1;
                        TmpByte = 0x80;
                }
		//TmpByte <<= 7;
		R_Byte2 = (R_Byte2>>1);//R_Byte2 >>= 1;
		R_Byte2 |= TmpByte;

		prt_set_clk();
		delay_nus(1);//delay_nus(2);
		prt_clear_clk();
		delay_nus(1);//delay_nus(2);
	}
	R_Byte >>= 4;
	R_Byte2 >>= 4;
	R_Byte = (R_Byte2 * 10) + R_Byte;
	return R_Byte;	
}




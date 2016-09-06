#include "includes.h"
#define DS1302_C

 unsigned char b10;
 unsigned char bpm;
/**************************************************************************************/
//������	��get_hours
//����		��˽��
//����		�����Сʱ
//�������	����
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
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
//������	��readbyte
//����		��˽��
//����		�� 
//�������	��
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
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
//������	��write_byte
//����		��˽��
//����		�� 
//�������	�� 
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
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
//������	��reset
//����		��˽��
//����		�� 
//�������	�� 
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
/**************************************************************************************/
void reset(void)		//sets the pins to begin and end the ds1302 communication
{
	ddr_set_rst();
	prt_clear_clk();
	prt_clear_rst();
	prt_set_rst();
}
/**************************************************************************************/
//������	��write
//����		��˽��
//����		�� 
//�������	�� 
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
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
//������	��LCD_DispXY
//����		��˽��
//����		���趨��ʾλ��
//�������	��posx,posy �趨������  ���Ͻ�Ϊ 0,0
//�������	��
//����ֵ	��
//�޸�����	��
//�޸���	��
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




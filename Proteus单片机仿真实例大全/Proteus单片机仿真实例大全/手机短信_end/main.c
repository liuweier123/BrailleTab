/*******************************************************************************
* ��������    ��
* ��������    ��
* ����        ��
* 
* ����ֵ      ��
* ����        ��
* ��������    ��
* ȫ�ֱ���    ��
* ȫ�־�̬������
* �ֲ���̬������
*----------------------------------------�޸���ʷ-------------------------------
* ��ǰ�汾    ��              �޸��ˣ�                  �޸����ڣ�
* �޸�˵��    ��
*----------------------------------------��ϵ����-------------------------------
* ��������    ��mcu_china@sina.com      at89c58@163.com 
*-----------------------δ������ͬ�⣬��������������;--------------------------
*******************************************************************************/
#include<reg52.h>
#include<absacc.h>
#include"LCD.h"
#include"serial.h"
#include"main.h"
#include"iic.h"
#include"key.h"	

uchar idata recive_buffer[64]={"                                                                "};
uchar re_data,recive_tept=0;
uchar count;
uchar m_count;
uchar disp_count; 
uint idata time;
bit flag;
bit key_flag;

void main()
{ 
 init_mcu();       
 init_lcd(); 
 init_iic();
 while(1)
 {		
	recive_string();	    
	key_handle();	
	disp_init_string();		
 }
}

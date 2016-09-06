/*******************************************************************************
* 函数名称    ：
* 功能描述    ：
* 参数        ：
* 
* 返回值      ：
* 作者        ：
* 创建日期    ：
* 全局变量    ：
* 全局静态变量：
* 局部静态变量：
*----------------------------------------修改历史-------------------------------
* 当前版本    ：              修改人：                  修改日期：
* 修改说明    ：
*----------------------------------------联系作者-------------------------------
* 作者邮箱    ：mcu_china@sina.com      at89c58@163.com 
*-----------------------未经作者同意，不得用于其它用途--------------------------
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

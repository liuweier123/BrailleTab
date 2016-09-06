#define ulong		unsigned long
#define uint		unsigned int
#define uchar		unsigned char

#include "xwj_lcd16.h"	 				// 字符液晶控制函数声明    //
#include "xwj_lcd6963.h"			// T6963C 公用函数
#include "xwj_fk.h"
#include "xwj_serial.h"		//串口函数集
#include "xwj_hlkey.h"			//  P1口行列式键盘  //


// ---------------------------------------------- //	32字节
void delay(uint x)
{
   uint i,j;
   for (i=0; i<x;i++) {
      for (j=0;j<102; j++) ;
   }
}

//--------------------------------------------------------------------------//
void main(void)						// 测试用
{
	serial_init();
	Lcd6963Init();					//Lcd6963复位
	Lcd16Reset();					//Lcd16复位
	Serial_main();					//	串口测试用主函数  
	Lcd16main();					//Lcd16临时测试主程序
	delay(1000);
	Lcd6963main();					//Lcd6963测试用
//	Lcd6963Cls();
	fk_init();						//方块初始化
	while(1)
	{
		if (~fk_run)
			fk_init();				//方块初始化
		fk_move();					//移动方块
		delay(10);
	}
}


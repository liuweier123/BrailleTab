/*--------------------------------------------------*/
/*             AVR-ARM开发网论坛                    */
/*           http://www.avrarm.com                  */
/*            AVR生成代码测试程序                   */
/*--------------------------------------------------*/
/*     程序由AVR辅助开发工具V2.1.0自动生成          */
/*     AVR系统的处理器为：   ATMega16               */
/*     AVR系统的晶振频率：   8.0000 Mhz             */
/*--------------------------------------------------*/

#include <iom16v.h>
#include "delay.h"

/*-----------------------------------------------------------------------
delay_us	   :1us延时函数
-----------------------------------------------------------------------*/
void delay_us(void)
{
   unsigned char t=2;
   t--;
}

/*-----------------------------------------------------------------------
delay_nus          :长延时函数

输入参数: t        :延时时间 us
-----------------------------------------------------------------------*/
void delay_nus(unsigned int t)
{
    while (t--)
       delay_us();
}

/*-----------------------------------------------------------------------
delay_ms	   :1ms延时函数
-----------------------------------------------------------------------*/
void delay_ms(void)
{
   delay_nus(1000);
}

/*-----------------------------------------------------------------------
delay_nms          :长延时函数

输入参数: t        :延时时间 ms
-----------------------------------------------------------------------*/
void delay_nms(unsigned int t)
{
    while (t--)
       delay_ms();
}

#define MAIN_C
/************************************************************************
;连线图: 液晶屏分为4 行*15列汉字使用间接操作方式
;*LCM--------------------------ATmega16*  
;*D0～D7                       PB0～PB7*
*CD                            PA2*
*RD                            PA1*
*WR                            PA0*
;************************************************************************/
/******************************************************/
/* 本程序在晓奇程序的基础上改编*/
/* Email: mymach@tom.com */
/******************************************************/

#include "includes.h"


void main(void) // 测试用
{
    unsigned char i;
    DDRA = 0xFF;
    PORTA = 0xff;
    shortdelay(1200);
    //MCUCR = 0x00;
    fnLCMInit();
    cls();
    cursor(0,0);
    dprintf(12,1,"test for:中文测试");
    dprintf(10,2,"T6963C use ATMega16");
    dprintf(10,3,"~mymach~");
    Linexy(5,5,80,5,8); // 画斜线1
    Linexy(5,5,80,20,8); // 斜线2
    Linexy(80,20,80,5,8); // 斜线3
    
    Linexy(2,2,238,2,8); // ------
    Linexy(2,2,2,62,8); // |
    circle(45,45,20,8); // 画圆 
    circle(45,45,21,8); // 画同心圆加粗 
    shortdelay(2000);
    
    while(1)
    {
        // 变化圆演示直径不断的变化由大到小再由小到大来回缩放
        for (i=20;i>5;i--)
        {
            circle(45,45,i+1,0); // 擦除外圆
            circle(45,45,i,8);
            circle(45,45,i-1,8);
            shortdelay(300);
        }
   
        shortdelay(500);
        for (i=5;i<20;i++)
        {
            circle(45,45,i-1,0); // 擦除内圆
            circle(45,45,i,8);
            circle(45,45,i+1,8);
            shortdelay(200);
        }
        shortdelay(300);
    }
}
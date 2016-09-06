#define NUMBER_C
#include "includes.h"

//计数处理函数
//参数p1：时间数组名
//参数p2：显示数组名
//功能：将计数值拆分为BCD码的10分，分；10秒，秒
void process(unsigned char *p1,unsigned char *p2)
{
    p2[0] = p1[0]/10;
    p2[1] = p1[0]-p2[0]*10;
    p2[2] = p1[1]/10;
    p2[3] = p1[1]-p2[2]*10;
}
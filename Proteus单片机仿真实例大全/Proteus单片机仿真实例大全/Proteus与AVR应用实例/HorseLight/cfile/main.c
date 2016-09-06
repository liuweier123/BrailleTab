#define MAIN_C
#include "includes.h"

void main(void)
{
    unsigned char i;
    DDRA  = 0xff;  //端口设置:PA设置为推挽1输出
    PORTA = 0xff;
    PORTA = 0x00;   //PORTA初始值为0，熄灭所有的LED
    delay_nms(10);
    while(1)
    {
        for(i=0;i<9;i++)
        {
            horse(i);
            delay_nms(20);
        }
        for(i=7;i>0;i--)
        {
            horse(i);
            delay_nms(20);
        }
    }    
}
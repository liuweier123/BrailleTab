#define MAIN_C
#include "includes.h"
/*************************************************************/
/*T0工作在定时方式*/ 
/*定时器采用8MHz系统时钟的256分频作为定时时钟*/
/*即每32 us计一个数，每计250个数（8ms)溢出一次*/
/*中断复位程序统计计数次数，计数125次时，秒钟加1*/
/*************************************************************/
//数码管字形表
//数码管为公阴极
unsigned char table[10] = 
{
  0x3f,   //0
  0x06,   //1
  0x5b,   //2
  0x4f,   //3
  0x66,   //4
  0x6d,   //5 
  0x7d,   //6 
  0x07,   //7 
  0x7f,   //8
  0x6f    //9
};

void display(unsigned char *p)
{
    unsigned char i;
    unsigned sel = 0x08;
    for(i=0;i<4;i++)
    {
        ConPort = ~sel;
        OutPort = table[p[i]];
        delay_nms(1);
        sel = sel>>1;
    }
}




void main(void)
{
   // unsigned char load;
    InitIo();
    PORTA = 0xff;  //点亮测试所有数码管
    PORTC = 0x00;   
    delay_nms(20);
    PORTC = 0xff;   //熄灭所有数码管
    TCCR0 |= (1<<CS02);//T/C0工作于定时方式，系统时钟256分频
    TCNT0 = 0x06;    //计数初值
    TIMSK |= (1<<TOIE0);  //使能T0溢出中断
    SREG |= (1<<7);  //使能全局中断
    while(1)
    {
        process(timer,data);
        display(data);
    }
}

#pragma vector = TIMER0_OVF_vect
    __interrupt void TOver0_isr( void )
{
    CNT++;
    if(CNT==TIMES)
    {
        CNT = 0;
        timer[1]++;
        if(timer[1]==60)
        {
            timer[1] = 0;
            timer[0]++;
        }
        if(timer[0]==60)
        {
            timer[0] = 0;
        }
    }
}  

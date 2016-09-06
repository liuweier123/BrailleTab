#define MAIN_C
#include "includes.h"
/***********************************************/
/*数码管应用*/
/***********************************************/
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

void GetKey(void)
{
    while((PINB&0x01) == 0)
    {
        KeyUp = 1;
        display(data);
    }
    while((PINB&0x02) == 0)
    {
        KeyDown = 1;
        display(data);
    }
}



void main(void)
{
    unsigned char i;
    InitIo();
    PORTA = 0xff;  //点亮测试所有数码管
    PORTC = 0x00;   
    delay_nms(20);
    PORTC = 0xff;
    while(1)
    {
        GetKey();  //按键扫描
        if(KeyUp == 1)
        {
            if(CNT != 9999)
            {
                CNT++;
                KeyUp = 0;
            }
        }
        if(KeyDown == 1)
        {
            if(CNT != 0)
            {
                CNT--;
                KeyDown = 0;
            }
        }
        process(CNT,data);
        display(data);
    }
}
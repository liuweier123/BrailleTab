#define MAIN_C
#include "includes.h"
/***************************/
/*PWM*/
/*晶振为4MHz*/
/*利用Timer1的OC1A脚输出占空比可调的信号*/
/*通过按键控制OCR1A的值*/
/***************************/

#define PwmOut     PD5     //A通道的PWM输出
#define OCR        OCR1A
#define KeyUp      PA0     //增大PWM值的按键
#define KeyDown    PA1     //减小PWM值的按键
#define Above      PA2     //设置位值过高指示
#define Below      PA3     //设置位值过低指示
#define STEP       64      //定义按键时的步进值
int OcrReg = 1024;         //OCR1A初始值
int Icr1Reg = 0x7ff;       //PWM的计数顶部值  Icr1Reg = 2047
//unsigned char *show = "0000"; 
unsigned char temp;

void init(void)   //初始化函数
{
    //比较匹配时清零，计数到最大时置位OC1A
    TCCR1A |= (1<<COM1A1)|(1<<WGM11);  
    //11位分辨率，快速PWM模式，使用系统时钟作为计数时钟
    TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS10);
    ICR1   = Icr1Reg;  
    OCR    = 0 ;
    DDRD  |= (1<<PwmOut);          //置PWM为输出
    DDRA  |= (1<<Above)|(1<<Below);      //指示灯定义为输出
    DDRA  &= ~((1<<KeyUp)|(1<<KeyDown)); //按键定义为输入
    PORTA |= (1<<KeyUp)|(1<<KeyDown);    //按键开启上拉
    PORTA |= (1<<Above)|(1<<Below);      //关闭两个指示灯
    //TIMSK |= (1<<OCIE1A);   //允许计数器比较匹配中断
    //SREG  |= (1<<7);   //开全局中断
}

void  ShowValue(int value)
{
    unsigned char *temp = "0000";
    temp[0] = value/1000 + 0x30;
    value = value%1000;
    temp[1] = value/100 +0x30;
    value = value%100;
    temp[2] = value/10 + 0x30;
    value = value%10;
    temp[3] = value + 0x30;  
    ClearLine(2);
    LCD_DisplayString(2,1,"OCR1A = ");
    LCD_DisplayString(2,9,temp);  
}
 
void main(void)
{ 
    unsigned char i; 
    init();
    Init_LCD();
    OCR = OcrReg;
    LCD_DisplayString(1,1,"PWM test");
    LCD_DisplayString(2,1,"OCR1A = ");
    ShowValue(OcrReg);
    while(1)
    {                
        if(!(PINA&(1<<KeyUp)))
        {
            delay_nms(10);    //按键消抖
            if(!(PINA&(1<<KeyUp)))
            {
                while(!(PINA&(1<<KeyUp)));  //等待按键释放
                if(OcrReg >= (Icr1Reg+1))
                {
                    for(i=0;i<5;i++)
                    {
                        PORTA ^= (1<<Above);
                        delay_nms(200);
                    }
                    ClearLine(2);
                    LCD_DisplayString(2,1,"Value MAX!");
                }
                else
                {
                    PORTA |= (1<<Above);
                    OcrReg += STEP;                    
                    OCR = OcrReg;
                    ShowValue(OcrReg);
                }
            }
        }
        if(!(PINA&(1<<KeyDown)))
        {
            delay_nms(10);    //按键消抖
            if(!(PINA&(1<<KeyDown)))
            {
                while(!(PINA&(1<<KeyDown)));  //等待按键释放
                if(OcrReg <= 0)
                {
                    for(i=0;i<5;i++)
                    {
                        PORTA ^= (1<<Below);
                        delay_nms(200);
                    }
                     ClearLine(2);
                    LCD_DisplayString(2,1,"Value MIN!");
                }
                else
                {
                    PORTA |= (1<<Below);
                    OcrReg -= STEP;
                    OCR = OcrReg;
                    ShowValue(OcrReg);
                }
            }
        }       
    }
}


//比较中断子程序，可以用来产生正弦波
/*#pragma vector = TIMER1_COMPA_vect
    __interrupt void CompA_isr( void ) 
{
    
    OcrReg =  st[j];
    OCR = OcrReg;  
    j++;  
    if(j>88)
    {
        j = 0;
    }
}*/
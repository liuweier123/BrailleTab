#define MAIN_C
#include "includes.h"
/*************************************************************/
/*T0�����ڶ�ʱ��ʽ*/ 
/*��ʱ������8MHzϵͳʱ�ӵ�256��Ƶ��Ϊ��ʱʱ��*/
/*��ÿ32 us��һ������ÿ��250������8ms)���һ��*/
/*�жϸ�λ����ͳ�Ƽ�������������125��ʱ�����Ӽ�1*/
/*************************************************************/
//��������α�
//�����Ϊ������
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
    PORTA = 0xff;  //�����������������
    PORTC = 0x00;   
    delay_nms(20);
    PORTC = 0xff;   //Ϩ�����������
    TCCR0 |= (1<<CS02);//T/C0�����ڶ�ʱ��ʽ��ϵͳʱ��256��Ƶ
    TCNT0 = 0x06;    //������ֵ
    TIMSK |= (1<<TOIE0);  //ʹ��T0����ж�
    SREG |= (1<<7);  //ʹ��ȫ���ж�
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

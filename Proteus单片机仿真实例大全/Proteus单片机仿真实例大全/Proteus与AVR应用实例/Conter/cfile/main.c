#define MAIN_C
#include "includes.h"
/***************************************************/
/*T0�����ڼ�����ʽ*/
/*���������PB0(T0)������*/
/***************************************************/
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
    unsigned char load;
    InitIo();
    PORTA = 0xff;  //�����������������
    PORTC = 0x00;   
    delay_nms(10);
    PORTC = 0xff;   //Ϩ�����������
    TCCR0 |= (1<<CS02)|(1<<CS01);//T/C0�����ڼ�����ʽ���½��ش���
    TCNT0 = CNT;    //������ֵ
    while(1)
    {
        load = TCNT0;
        process(load,data);
        display(data);
    }
}
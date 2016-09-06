#define MAIN_C
#include "includes.h"
/***************************/
/*����ͨ��*/
/*����Ϊ4MHz*/
/*������Ϊ9600bps*/
/*���Ͳ��ò�ѯ��ʽ���жϲ��ý��շ�ʽ*/
/*���յ����ַ��ﵽ������ĳ���ʱ������LCD����ʾ�յ����ַ�*/
/***************************/
#define BufSize 10
unsigned char RsBuf[BufSize];  //������ջ�����
int RsBytes = 0;
unsigned char flag = 0;
void main(void)
{
    unsigned char *msg = "Usart Test!\n";    
    SREG |= (1<<7);  //ʹ��ȫ���ж�
    UsartInit();
    Init_LCD();
    SendNbyte(msg,12);
    PutStr("Test Ok\n");   
    LCD_DisplayString(1,1,"Usart Test!");
    delay_nms(2000);
    LCD_Clear();
    LCD_DisplayString(1,1,"Recive is :");    
    while(1)
    {
        if(flag)
        {
           PutStr(RsBuf);
           LCD_DisplayString(2,1,RsBuf);           
           PutChar('\n');
           flag = 0;
        }
    }
}

//�����ж��ӳ���  
#pragma vector = USART_RXC_vect
    __interrupt void RXC_isr( void )
{
    RsBuf[RsBytes] = UDR;
    RsBytes ++;
    //PutChar(RsBuf[RsBytes]); //����
    if(RsBytes > BufSize)
    {   
        flag = 1;
        RsBytes = 0;
    }
}  


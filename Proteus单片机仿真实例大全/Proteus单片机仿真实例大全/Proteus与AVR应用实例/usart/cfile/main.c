#define MAIN_C
#include "includes.h"
/***************************/
/*串口通信*/
/*晶振为4MHz*/
/*波特率为9600bps*/
/*发送采用查询方式，中断采用接收方式*/
/*当收到的字符达到所定义的长度时，则在LCD上显示收到的字符*/
/***************************/
#define BufSize 10
unsigned char RsBuf[BufSize];  //定义接收缓冲器
int RsBytes = 0;
unsigned char flag = 0;
void main(void)
{
    unsigned char *msg = "Usart Test!\n";    
    SREG |= (1<<7);  //使能全局中断
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

//接收中断子程序  
#pragma vector = USART_RXC_vect
    __interrupt void RXC_isr( void )
{
    RsBuf[RsBytes] = UDR;
    RsBytes ++;
    //PutChar(RsBuf[RsBytes]); //回显
    if(RsBytes > BufSize)
    {   
        flag = 1;
        RsBytes = 0;
    }
}  


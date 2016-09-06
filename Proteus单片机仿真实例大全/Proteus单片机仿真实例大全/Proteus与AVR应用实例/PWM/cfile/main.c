#define MAIN_C
#include "includes.h"
/***************************/
/*PWM*/
/*����Ϊ4MHz*/
/*����Timer1��OC1A�����ռ�ձȿɵ����ź�*/
/*ͨ����������OCR1A��ֵ*/
/***************************/

#define PwmOut     PD5     //Aͨ����PWM���
#define OCR        OCR1A
#define KeyUp      PA0     //����PWMֵ�İ���
#define KeyDown    PA1     //��СPWMֵ�İ���
#define Above      PA2     //����λֵ����ָʾ
#define Below      PA3     //����λֵ����ָʾ
#define STEP       64      //���尴��ʱ�Ĳ���ֵ
int OcrReg = 1024;         //OCR1A��ʼֵ
int Icr1Reg = 0x7ff;       //PWM�ļ�������ֵ  Icr1Reg = 2047
//unsigned char *show = "0000"; 
unsigned char temp;

void init(void)   //��ʼ������
{
    //�Ƚ�ƥ��ʱ���㣬���������ʱ��λOC1A
    TCCR1A |= (1<<COM1A1)|(1<<WGM11);  
    //11λ�ֱ��ʣ�����PWMģʽ��ʹ��ϵͳʱ����Ϊ����ʱ��
    TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS10);
    ICR1   = Icr1Reg;  
    OCR    = 0 ;
    DDRD  |= (1<<PwmOut);          //��PWMΪ���
    DDRA  |= (1<<Above)|(1<<Below);      //ָʾ�ƶ���Ϊ���
    DDRA  &= ~((1<<KeyUp)|(1<<KeyDown)); //��������Ϊ����
    PORTA |= (1<<KeyUp)|(1<<KeyDown);    //������������
    PORTA |= (1<<Above)|(1<<Below);      //�ر�����ָʾ��
    //TIMSK |= (1<<OCIE1A);   //����������Ƚ�ƥ���ж�
    //SREG  |= (1<<7);   //��ȫ���ж�
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
            delay_nms(10);    //��������
            if(!(PINA&(1<<KeyUp)))
            {
                while(!(PINA&(1<<KeyUp)));  //�ȴ������ͷ�
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
            delay_nms(10);    //��������
            if(!(PINA&(1<<KeyDown)))
            {
                while(!(PINA&(1<<KeyDown)));  //�ȴ������ͷ�
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


//�Ƚ��ж��ӳ��򣬿��������������Ҳ�
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
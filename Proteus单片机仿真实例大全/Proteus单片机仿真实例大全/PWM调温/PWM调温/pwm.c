#include <reg52.h>
//#include <at89x52.h>
//#include <keyscan.h>
extern void scan_full(void);
extern unsigned char key_scan(void);
extern bit key_ok;
unsigned char pwm_set,key_value;
unsigned char count;
sbit PWM=P3^6;
bit up,down,set_flag;
unsigned char code BCD[]={0x3f,0x06,0x5b,0x4f, //�˴��ǽ�0-Fת������Ӧ��BCD��
                          0x66,0x6d,0x7d,0x07, 
                          0x7f,0x6f,0x77,0x7c, 
                          0x39,0x5e,0x79,0x71};
void delay1(unsigned char t)
{
 while(t--);
}



void pwm(void) interrupt 5//��ʱ��2����PWM����
{
	TF2=0;					//��ʱ��2�������־Ҫ������,
							//����RCLK��TCLKΪ1ʱ��Ӳ�����
	if((count>=pwm_set)&&(count<10))
		PWM=1;
	else	PWM=0;	
	count++;	
	if(count==10)
	count=0x00;
	
}


void key_pwm(unsigned char x)//�Ѽ�ֵת��ΪPWM����ֵ
{
	switch(x)				//�Ѿ������ת��Ϊ��������
	{
		case 1:up=1;break;
		case 2:down=1;break;
		case 3:set_flag=!set_flag;break;
		default:break;
	}
	
	if(up&&set_flag)		//����PWM����:pwm_set
	{
		pwm_set++;
		up=0;
		if(pwm_set>=10)
		pwm_set=0x00;
	}
	if(down&&set_flag)
	{
		pwm_set--;
		down=0;
		if(pwm_set==0xff)
		pwm_set=9;
	}
	if(!set_flag)
	{
		up=0;
		down=0;
	}
}


void main(void)
{
	TH2=0xb1;	//��ʱ20MS
	TL2=0xe0;
	RCAP2H=0xb1;//��ʱ��2���ʱ��������Ԫ�������͵�TH2��TL2��
 	RCAP2L=0xe0;
	EA=1;
	ET2=1;
	TR2=1;
	while(1)
	{
		scan_full();	//���Ƿ��м�����
		if(key_ok)		//�м�����,���жϵ������ĸ�������
		{
			key_value=key_scan();//��ֵ��key_value�ݴ�
			P0=~BCD[key_value];	 /*�������ǽ���ֵ��ʾ����*/
  			P2=0xfe;			/**						 */
			delay1(200);		/*************************/
			key_pwm(key_value);  //���ü�ֵתPWM���ò�������
			key_value=0x00;		 //�����ֵ,����һ�ΰ���,�����Ӧ
		}
		P0=~BCD[pwm_set];		/***�������ǽ�pwm_setֵ��ʾ����*/
		P2=0xfd;				/*******					*/
		delay1(200);			/****************************/
	}
}

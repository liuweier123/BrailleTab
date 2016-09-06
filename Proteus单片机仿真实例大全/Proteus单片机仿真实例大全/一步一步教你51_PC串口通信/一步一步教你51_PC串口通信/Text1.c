#include <reg51.h>
#include <intrins.h>

unsigned char key_s, key_v, tmp;
char code str[] = "I love zhu xiao ying--CUMT \n\r";

void send_int(void);
void send_str();
bit	scan_key();
void proc_key();
void delayms(unsigned char ms);
void send_char(unsigned char txd);

sbit	K1 = P1^4;

main()
{
    send_int();
	TR1 = 1;			            	// ������ʱ��1
	while(1)
	{
		if(scan_key())	            	// ɨ�谴��
		{
			delayms(10);			// ��ʱȥ����
			if(scan_key())			// �ٴ�ɨ��
			{
				key_v = key_s;		// �����ֵ
				proc_key();			// ������
			}
		}
		if(RI)						// �Ƿ������ݵ���
		{
			RI = 0;
			tmp = SBUF;				// �ݴ���յ�������
			P0 = tmp;				// ���ݴ��͵�P0��
			send_char(tmp);			// �ش����յ�������
		}	
	}

}
void send_int(void)
{     TMOD = 0x20;			// ��ʱ��1������8λ�Զ�����ģʽ, ���ڲ���������
	TH1 = 0xF3;				// ������2400
	TL1 = 0xF3;
	SCON = 0x50;			// �趨���пڹ�����ʽ
	PCON&= 0xef;			// �����ʲ�����
		

	IE = 0x0;				// ��ֹ�κ��ж�
}
bit scan_key()	
// ɨ�谴��                               
{
	key_s = 0x00;
	key_s |= K1;
	return(key_s ^ key_v);	
}

void proc_key()
// ������
{
	if((key_v & 0x01) == 0)
	{			// K1����
		send_str();				// �����ִ�
	}
}

void send_char(unsigned char txd)
// ����һ���ַ�
{
	SBUF = txd;
	while(!TI);				// �������ݴ���
	TI = 0;					// ������ݴ��ͱ�־
}

void send_str()
// �����ִ�
{
	unsigned char i = 0;
	while(str[i] != '\0')
	{
		SBUF = str[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	}	
}

void delayms(unsigned char ms)	
// ��ʱ�ӳ���
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}

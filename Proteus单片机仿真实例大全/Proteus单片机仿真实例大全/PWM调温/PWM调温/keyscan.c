#include <reg52.h>
//#include <at89x52.h>
//unsigned char code BCD[]={0x3f,0x06,0x5b,0x4f, //�˴��ǽ�0-Fת������Ӧ��BCD��
//                          0x66,0x6d,0x7d,0x07, 
//                          0x7f,0x6f,0x77,0x7c, 
//                          0x39,0x5e,0x79,0x71};
//unsigned char code KEY[]={0x00,0x00,0x01,0x02,0x03,//�˴���Ϊʹ����ͨ��,����ֵ���ǰ�
//						  	   0x04,0x05,0x06,0x07,//�������ʱ,�Ѵ˱���ļ���
//							   0x08,0x09,0x0a,0x0b,//��ǰ����Ǹ�0x00��Ϊ�˲����,
//							   0x0c,0x0d,0x0e,0x0f};//��Ϊ��ֵ�Ǵ�1��ʼ��
							
sfr key_port=0x90;	    //����P1��Ϊ����ɨ���
bit key_ok=0;       	//�м����µı�־

/*************��ʱ�ӳ���*************
****����һ����ʱ18΢��,tÿ��1,��ʱ����6΢��*/
void delay(unsigned char t)
{
 while(t--);
}


unsigned char r_left(unsigned char x)//ѭ������һλ
{
 x<<=1;
 x++;
 return(x);
}

/*************�������޼�����**********
****�м�������key_ok��1************/
void scan_full(void)
{
	unsigned char temp;
	key_port=0xf0; 		//�Ͱ��ֽ�Ϊ����,�߰��ֽ�Ϊ����
	temp=P1;
	if(temp!=0xf0)
	key_ok=1;
	else key_ok=0;
}
/************����ɨ�����*************************
****����:���ؼ�ֵ,���޼�����ʱ,����0*************/
 unsigned char key_scan(void)
{
 unsigned char temp,count=0x01,key_value;//��������ֵ
 unsigned char x_scan=0xfe,y_scan=0xef;//�С���ɨ����
 unsigned char i,j,y;		//����������
 while(1)
 {
 	scan_full();	 		//�����Ƿ��м�����
 	if(key_ok==1)
 	{
   		key_ok=0;
   		delay(200);			//��ʱȥ����
   		scan_full();			//�ٴδ����Ƿ��м�����
   		if(key_ok==1)
   		{
    		for(i=0;i<4;i++)		//ɨ��4��
    		{
	 			key_port=x_scan;
     			for(j=0;j<4;j++)		//ÿ��4��
     			{
      				temp=key_port;
	  				temp=temp&0xf0;
	  				y=y_scan&0xf0;
	  				if(temp==y)
	  				{
						while(key_ok!=0)//�ȴ������ɿ�
   						{
							scan_full();
   						}
	   					key_value=count;												
	   					return(key_value);//�ҵ���ֵ,���Ϸ���
	  				}
	  				else 
	  				{
	   					count++;
	   					y_scan=r_left(y_scan);
	  				}	 
	 			}
				y_scan=0xef;		//ɨ����һ��,���¶���ɨ��������ֵ
	 			x_scan=r_left(x_scan);//��ɨ��������һλ,ɨ����һ��  					
			}
		}
  	} 
    return(key_value);//û������,����0
 }
}

//unsigned char key(void)
//{
 // unsigned char x;
 // unsigned char y;
 // x=key_scan();
 // return(x);
  //y=KEY[x];	
  //return y;
//}

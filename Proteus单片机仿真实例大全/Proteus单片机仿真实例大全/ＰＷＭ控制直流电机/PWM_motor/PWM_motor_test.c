  /*��PWM���Ƶ������Ƶ��Ӧ������25HZ��35HZ֮��*/
  /*��ʱ1ms,1������30ms,����Ƶ��Ϊ33HZ		   */			
  /*										   */
    
#include   <reg51.h>   
  typedef   unsigned   char   uchar;   
  sbit   P0_0=P0^0;
  sbit   P0_1=P0^1; 
  sbit   P0_2=P0^2;
  sbit   P0_3=P0^3;
  sbit   P0_4=P0^4;
  sbit   P2_0=P2^0;
  sbit   P2_1=P2^1;
  sbit   P2_2=P2^2;
  sbit   P2_3=P2^3;
  sbit   P2_4=P2^4;
  sbit   P3_4=P3^4;   
 
  uchar   time=0;   
  uchar   period=30;   
  uchar   high=10; 
  uchar   th0=0;
  uchar   tl0=1;
  bit    dir;
  
    
  void dealy()
  {
   uchar i;
   for(i=0;i<100;i++);

  }


  
  void   timer0()   interrupt   1   using   1   
  {   
            TH0=0xfc;     /*��ʱ����ֵ��װ��*/   
            TL0=0x18;
            
            time++; 
			P3_4=~P3_4;  
      if(dir==1)
	  {
			
			if(time==high)   /*�ߵ�ƽ����ʱ����������*/   
               P2_0=th0;		 /*��������������*/
			    
			    
            else   if(time==period)     /*����ʱ�䵽�����*/   
                      {   time=0;   
                          P2_0=tl0;		/*��������������*/
						  
						   
                      }   
    		  
		}
		 else	  if(time==high)   /*�ߵ�ƽ����ʱ����������*/   
            
			   P2_1=th0;		 /*��������������*/
			    
			   
                  else   if(time==period)     /*����ʱ�䵽�����*/   
                      {   time=0;   
                          P2_1=tl0;		/*��������������*/
						  
                      }
    
       	
} 



 void   main()   
  {   

		P0=0x00;
		P2=0x00;

        TMOD=0x01;   /*��ʱ��0��ʽ1*/   
        TH0=0xfc;     /*��ʱ��װ�س�ֵ�����������źŵ�ռ�ձ�Ϊ1��5*/   
        TL0=0x18; 
		
         
        ET0=1;   /*����ʱ��0�ж�*/   
        TR0=1;    /*������ʱ��0*/ 
	
	
	

        while(1)    
        {
			if(P0_0==1)
	        EA=1;     /*��CPU�ж�*/

		 	if(P0_1==1)
			EA=0;	 /*��CPU�ж�*/

			if(P0_2==1)
			{
			dir=~dir;  /*ת�����*/
			while(P0_2!=0)
			{};

			}

			if(P0_3==1)
			{

			 high++;
			 if(high==30)
			 high=0;
			while(P0_3!=0)
			{};
			 }
		 }   
    

}	
   


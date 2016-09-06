  /*用PWM控制电机脉冲频率应控制在25HZ～35HZ之间*/
  /*定时1ms,1个周期30ms,脉冲频率为33HZ		   */			
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
            TH0=0xfc;     /*定时器初值重装载*/   
            TL0=0x18;
            
            time++; 
			P3_4=~P3_4;  
      if(dir==1)
	  {
			
			if(time==high)   /*高电平持续时间结束，变低*/   
               P2_0=th0;		 /*经过反相器反相*/
			    
			    
            else   if(time==period)     /*周期时间到，变高*/   
                      {   time=0;   
                          P2_0=tl0;		/*经过反相器反相*/
						  
						   
                      }   
    		  
		}
		 else	  if(time==high)   /*高电平持续时间结束，变低*/   
            
			   P2_1=th0;		 /*经过反相器反相*/
			    
			   
                  else   if(time==period)     /*周期时间到，变高*/   
                      {   time=0;   
                          P2_1=tl0;		/*经过反相器反相*/
						  
                      }
    
       	
} 



 void   main()   
  {   

		P0=0x00;
		P2=0x00;

        TMOD=0x01;   /*定时器0方式1*/   
        TH0=0xfc;     /*定时器装载初值，设置脉冲信号的占空比为1／5*/   
        TL0=0x18; 
		
         
        ET0=1;   /*开定时器0中断*/   
        TR0=1;    /*启动定时器0*/ 
	
	
	

        while(1)    
        {
			if(P0_0==1)
	        EA=1;     /*开CPU中断*/

		 	if(P0_1==1)
			EA=0;	 /*关CPU中断*/

			if(P0_2==1)
			{
			dir=~dir;  /*转向控制*/
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
   


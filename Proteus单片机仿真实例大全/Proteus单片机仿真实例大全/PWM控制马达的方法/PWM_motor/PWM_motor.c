  /*以下是一段产生占空比为20%的脉冲信号的c51程序，我想电机转速*/
  /*对应于一定的占空比，如果你要改变占空比，可能需要建立一个对应*/
  /*于不同转速的参数表（如定时器初值等），查表*/
  /*得到不同参数，以改变占空比和转速。你用什么驱动电路？*/
   														
  /*采用6MHz晶振，在P1.0脚上输出周期为2.5s,占空比为20%的脉冲信号*/   
  /*定时100ms,周期2.5s需25次中断，高电平0.5s需5次中断*/   
    
#include   <reg51.h>   
  typedef   unsigned   char   uchar;   
  sbit   P0_0=P0^0;
  sbit   P0_1=P0^1; 
  sbit   P0_2=P0^2;
  sbit   P0_3=P0^3; 
  sbit   P2_0=P2^0;
  sbit   P2_1=P2^1; 
  uchar   time=0;   
  uchar   period=25;   
  uchar   high=10;
  uchar   th1=0;
  uchar   tl1=0;
  uchar   th0=0;
  uchar   tl0=0;     
    
  void   timer0()   interrupt   1   using   1   
  {   
            TH0=0x3c;     /*定时器初值重装载*/   
            TL0=0xb0;
            //TH0=0xc3;/*定时器初值重装载*/
			//TL0=0x50;  
            time++;   
            if(time==high)   /*高电平持续时间结束，变低*/   
            {   P2_0=tl0;
			    P2_1=tl1;		
			  }   
            else   if(time==period)     /*周期时间到，变高*/   
                      {   time=0;   
                          P2_0=th0;
						  P2_1=th1;
						     
                      }   
    
  }   
    
  void   main()   
  {   
        TMOD=0x01;   /*定时器0方式1*/   
        TH0=0x3c;     /*定时器装载初值，设置脉冲信号的占空比为1／5*/   
        TL0=0xb0; 
		//TH0=0xc3;/*定时器装载初值,设置脉冲信号的占空比为4／5*/
		//TL0=0x50;    
        EA=1;     /*开CPU中断*/   
        ET0=1;   /*开定时器0中断*/   
        TR0=1;/*启动定时器0*/  
		
		if(P0_2==1)
		 {
		  th0=1;
		  tl0=0;
    	  th1=0;
		  tl1=0;
		      }

          if(P0_3==1)
		 {
		  th0=0;
		  tl0=0;
    	  th1=1;
		  tl1=0;
		      }
		while(1)     /*等待中断*/   
        {}   
    
  }   

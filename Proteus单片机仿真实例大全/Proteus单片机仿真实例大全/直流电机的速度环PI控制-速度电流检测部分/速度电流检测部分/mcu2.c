//从机的查询程序。


#include <reg51.h>
#define uchar unsigned char
uchar f1=0x00;
uchar j,k;
void main (void)
{
    
	SCON=0x90; //MODER1,REN=1;   //允许接受信息
	PCON=0x00;

        while(1)
       {
           do{
               while(RI==0);RI=0;
           }while(SBUF!=0xff);
        
         SBUF=0xbb;
         while(TI==0);TI=0;
		 
     
         while(RI==0);RI=0;			
         f1=SBUF;
            
	 P2=f1;
        }
}

        

			

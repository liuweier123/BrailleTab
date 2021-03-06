#include <atmel\regx52.h>

#define int8 unsigned char
#define int16 unsigned int
#define int32 unsigned long 

#define CTRL_PORT  P2
#define DATA_PORT  P0
#define ADDR_PORT  P1

int8 flag;
int8 n;
int8 zzz;
int8 yyy;
int8 code table[][32]={
{0x60,0x02,0x1C,0x0A,0x10,0x12,0x10,0x12,0x10,0x02,0xFF,0x7F,0x10,0x02,0x10,0x12,0x70,0x14,0x1C,0x0C,0x13,0x04,0x10,0x0A,0x90,0x49,0x10,0x50,0x14,0x60,0x08,0x40},/*"��",0*/

{0x00,0x20,0x00,0x20,0x3E,0x21,0x22,0x21,0x22,0x21,0x22,0x21,0x22,0x21,0x22,0x21,0x22,0x39,0xBE,0x27,0x22,0x21,0x02,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20},/*"��",1*/

{0x88,0x00,0x88,0x00,0x88,0x7F,0x48,0x00,0xDF,0x1F,0xA8,0x10,0x9C,0x12,0xAC,0x14,0xEA,0x7F,0x8A,0x12,0x89,0x14,0x88,0x10,0x88,0x7F,0x08,0x10,0x08,0x14,0x08,0x08},/*"÷",2*/

{0x08,0x20,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x08,0x21,0x04,0x21,0x04,0x20,0x02,0x00},/*"��",3*/

{0x00,0x04,0x7F,0x04,0x14,0x05,0x14,0x3F,0x7F,0x05,0xD5,0x04,0xD5,0x7F,0x75,0x00,0x43,0x00,0x41,0x3F,0x7F,0x21,0x41,0x21,0x41,0x21,0x7F,0x3F,0x41,0x21,0x00,0x00},/*"��",4*/

{0x00,0x00,0xFC,0x0F,0x00,0x04,0x00,0x02,0x00,0x01,0x80,0x00,0x80,0x00,0x80,0x20,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00}/*"��",5*/
};

int8 select_hc138[][4]={
{0x20,0x21,0x22,0x23},
{0x24,0x25,0x26,0x27},

{0x10,0x11,0x12,0x13},
{0x14,0x15,0x16,0x17},
{0x18,0x19,0x1a,0x1b},
{0x1c,0x1d,0x1e,0x1f}
};
void delay(void);
void ldelay(void);
void main(void){

int8 i,j,k;
int8 index;


flag=0x10;
n=0;
TMOD=0x01;
TH0=0xb1;
TL0=0xe0;
ET0=1;
EA=1;
//TR0=1;


flag=0x10;



yyy=0;
zzz=0;

//CTRL_PORT=select_hc138[2][0]; 

while(1)
{
    for(k=0;k<6;k++){   
	   for(j=0;j<60;j++)
	   	  {	    	
		    for(i=0;i<8;i++)
	     	{
		    	CTRL_PORT=select_hc138[k][0]; 
	     		DATA_PORT=table[k][2*i]; 

         		ADDR_PORT=i; 			        	  
	 			delay();

 				CTRL_PORT=select_hc138[k][1]; 
	     		DATA_PORT=table[k][2*i+1];
		    		
         		ADDR_PORT=i;  
 	 			delay();
	     	}		 	     
	    	for(i=8;i<16;i++)
	     	{
		    	CTRL_PORT=select_hc138[k][2]; 
	     		DATA_PORT=table[k][2*i]; 

				ADDR_PORT=i-8; 			        	   
	 			delay();

		    	CTRL_PORT=select_hc138[k][3]; 
	     		DATA_PORT=table[k][2*i+1];

        		ADDR_PORT=i-8;     
	 			delay();
	     	}	  
         }	

      
   }		 		 	 
  	 	 
  }


}
void ldelay(void){
int16 i;
for(i=0;i<1000;i++);

}
void delay(void){
int16 i;
for(i=0;i<80;i++);

}
void timer0() interrupt 1 using 3
{
 	TF0=0;
	TH0=0xb1;
	TL0=0xe0;
	if(n<100)
	{
	   n++;
	}
	else
	{

	   switch(flag)
	   {
	   	  case 0x10:
		  {
			  flag=0x11;		  
		  	  break;		  
		  }
	   	  case 0x11:
		  {
			  flag=0x12;		  
		  	  break;		  
		  }	   
	   	  case 0x12:
		  {
			  flag=0x13;		  
		  	  break;		  
		  }	  	   
	   	  case 0x13:
		  {
			  flag=0x20;		  
		  	  break;		  
		  }		   
	   	  case 0x20:
		  {
			  flag=0x21;		  
		  	  break;		  
		  }
	   	  case 0x21:
		  {
			  flag=0x22;		  
		  	  break;		  
		  }	   
	   	  case 0x22:
		  {
			  flag=0x23;		  
		  	  break;		  
		  }	  	   
	   	  case 0x23:
		  {
			  flag=0x10;		  
		  	  break;		  
		  }		   
	   }
	   n=0;
	   if(zzz==4)
	    {
	    zzz=0;
	  	}
        else
		{
	     zzz++;
	     yyy+=4;			
		}

	 }


}



















#include <atmel\regx52.h>

#define int8 unsigned char
#define int16 unsigned int
#define int32 unsigned long 


int8 code num_tab[][8]={
/*--8*8--����--����ɨ��--���򣨵�λ��ǰ��--*/

{0x00,0x00,0x00,0x38,0x44,0x38,0x00,0x00},/*"0",0*/
{0x00,0x00,0x40,0x78,0x48,0x00,0x00,0x00},/*"1",1*/
{0x00,0x00,0x00,0x4C,0x54,0x6C,0x00,0x00},/*"2",2*/
{0x00,0x00,0x00,0x74,0x4C,0x6C,0x00,0x00},/*"3",3*/
{0x00,0x00,0x00,0x7C,0x28,0x10,0x00,0x00},/*"4",4*/
{0x00,0x00,0x00,0x74,0x54,0x7C,0x00,0x00},/*"5",5*/
{0x00,0x00,0x70,0x54,0x54,0x38,0x00,0x00},/*"6",6*/
{0x00,0x00,0x04,0x7C,0x04,0x00,0x00,0x00},/*"7",7*/
{0x00,0x00,0x00,0x6C,0x54,0x6C,0x00,0x00},/*"8",8*/
{0x00,0x00,0x00,0x3C,0x54,0x1C,0x00,0x00},/*"9",9*/
{0x00,0x00,0x00,0x38,0x44,0x38,0x00,0x00},/*"0",10*/
{0x00,0x00,0x40,0x78,0x58,0x68,0x00,0x00},/*"a",11*/
{0x00,0x00,0x78,0x48,0x7C,0x00,0x00,0x00},/*"b",12*/
{0x00,0x00,0x00,0x48,0x48,0x70,0x00,0x00},/*"c",13*/
{0x00,0x00,0x00,0x7C,0x48,0x78,0x00,0x00},/*"d",14*/
{0x00,0x00,0x58,0x58,0x70,0x00,0x00,0x00},/*"e",15*/
{0x00,0x00,0x00,0x4C,0x7C,0x48,0x00,0x00},/*"f",16*/
{0x00,0x08,0xD8,0xD8,0xF8,0x00,0x00,0x00},/*"g",17*/
{0x00,0x00,0x78,0x08,0x7C,0x00,0x00,0x00},/*"h",18*/
{0x00,0x00,0x40,0x7C,0x48,0x00,0x00,0x00},/*"i",19*/
{0x00,0x00,0x00,0xFC,0x88,0x00,0x00,0x00},/*"j",20*/
{0x00,0x00,0x48,0x78,0x7C,0x00,0x00,0x00},/*"k",21*/
{0x00,0x00,0x40,0x7C,0x44,0x00,0x00,0x00},/*"l",22*/
{0x00,0x00,0x00,0x78,0x78,0x78,0x00,0x00},/*"m",23*/
{0x00,0x00,0x78,0x08,0x78,0x00,0x00,0x00},/*"n",24*/
{0x00,0x00,0x30,0x48,0x48,0x30,0x00,0x00},/*"o",25*/
{0x00,0x00,0x78,0xC8,0xF8,0x00,0x00,0x00},/*"p",26*/
{0x00,0x00,0x00,0xF8,0xC8,0x78,0x00,0x00},/*"q",27*/
{0x00,0x00,0x08,0x48,0x78,0x48,0x00,0x00},/*"r",28*/
{0x00,0x00,0x68,0x68,0x58,0x00,0x00,0x00},/*"s",29*/
{0x00,0x00,0x00,0x40,0x7C,0x08,0x00,0x00},/*"t",30*/
{0x00,0x00,0x78,0x40,0x78,0x00,0x00,0x00},/*"u",31*/
{0x00,0x08,0x38,0x40,0x38,0x08,0x00,0x00},/*"v",32*/
{0x00,0x08,0x78,0x18,0x68,0x18,0x00,0x00},/*"w",33*/
{0x00,0x00,0x48,0x78,0x78,0x48,0x00,0x00},/*"x",34*/
{0x00,0x00,0x08,0x38,0xD8,0x88,0x00,0x00},/*"y",35*/
{0x00,0x00,0x48,0x78,0x68,0x00,0x00,0x00}/*"z",36*/





};

void delay(void);

int8 n;
int8  delta_p;
int8  *p;

void main(void){


int8 i;
int8 j;


p=&num_tab[0][0];

TMOD=0x01;
TH0=0xfc;
TL0=0x18;
ET0=1;
EA=1;
TR0=1;


while(1)
{

   for(i=0;i<8;i++){
	     delay();
	     P0=*(p+delta_p);
         P2=i|0x18;



		 p++;
		 if(p>&num_tab[0][7])
	           p=&num_tab[0][0]; 
     } 
	 	 
}


}
void delay(void){
int16 i;
for(i=0;i<500;i++);

}


void timer0() interrupt 1 using 3
{
    TF0=0;
    TH0=0xfc;
    TL0=0x18;
    if(n<200)
    {
       n++;
    }
    else
    {
	     n=0;
		 if(delta_p>240)
	           delta_p=0; 
		 else
		       delta_p+=2; 
		 
	}
}






















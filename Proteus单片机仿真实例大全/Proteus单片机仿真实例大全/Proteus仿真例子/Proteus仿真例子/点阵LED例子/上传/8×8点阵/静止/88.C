#include <atmel\regx52.h>

#define int8 unsigned char
#define int16 unsigned int
#define int32 unsigned long 


int8 code num_tab[][8]={
/*--8*8--����--����ɨ��--���򣨵�λ��ǰ��--*/
{0x00,0x00,0x02,0x05,0x05,0x05,0x02,0x00},/*"0",0*/

{0x00,0x00,0x00,0x06,0x04,0x04,0x0E,0x00},/*"1",1*/

{0x00,0x00,0x07,0x05,0x02,0x01,0x07,0x00},/*"2",2*/

{0x00,0x00,0x07,0x03,0x04,0x05,0x07,0x00},/*"3",3*/

{0x00,0x00,0x04,0x06,0x05,0x06,0x04,0x00},/*"4",4*/

{0x00,0x00,0x07,0x01,0x07,0x05,0x07,0x00},/*"5",5*/

{0x00,0x00,0x06,0x01,0x0F,0x09,0x0E,0x00},/*"6",6*/

{0x00,0x00,0x0E,0x04,0x04,0x04,0x04,0x00},/*"7",7*/

{0x00,0x00,0x07,0x05,0x02,0x05,0x07,0x00},/*"8",8*/

{0x00,0x00,0x07,0x05,0x07,0x04,0x02,0x00},/*"9",9*/

{0x00,0x00,0x02,0x05,0x05,0x05,0x02,0x00}/*"0",10*/



};

void delay(void);
void main(void){


int8 i;
int8 j;




while(1)
{

      for(i=0;i<8;i++){
	 delay();
	 P0=num_tab[1][i];
         P2=i|0x18;
     }
	 	 
}


}
void delay(void){
int16 i;
for(i=0;i<500;i++);

}
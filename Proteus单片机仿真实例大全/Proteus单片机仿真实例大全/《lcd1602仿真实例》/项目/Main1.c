#include<reg51.h>
#include<LCD1602.h> 



void main(void)
{
 LCD_initial();
LCD_set_position(0);
LCD_printc('a');
LCD_prints("Input too long!");
LCD_set_position(0x40);
LCD_printc('a');
 while(1)
  {
   ;
  }
}

    
  



 



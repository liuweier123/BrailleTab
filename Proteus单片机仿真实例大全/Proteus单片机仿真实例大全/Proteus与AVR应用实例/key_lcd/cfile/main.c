#define MAIN_C
#include "includes.h"
void main(void)
{
    char key_code;
    unsigned char x_position;
    unsigned char *space = "                   ";
    Init_LCD();   
    //PORTD = 0xff; 
    //DDRD =  0xf0;     
    PORTA = 0xff;
    DDRA  = 0xf8;
    LCD_DisplayString(1,1,"key scan test");
    x_position = 2;
    while(1)
    {
         key_code = read_keybord();  
         //Õë¶Ô4X3µÄ¼üÅÌ         
         switch(key_code)   
         {  
            case 1:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('1');          
                break;
            case 2:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('2');          
                break;
            case 3:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('3');          
                break; 
            case 4:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('4');          
                break;
            case 5:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('5');          
                break;
            case 6:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('6');          
                break;
            case 7:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('7');          
                break;  
            case 8:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('8');          
                break;
            case 9:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('9');          
                break;            
            case 10:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('*');          
                break;
            case 11:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('0');          
                break;
             case 12:            
                LCD_Cursor(2,x_position);
                LCD_DisplayCharacter('#');          
                break;         
        }         
         //delay_nms(10);
    }
}
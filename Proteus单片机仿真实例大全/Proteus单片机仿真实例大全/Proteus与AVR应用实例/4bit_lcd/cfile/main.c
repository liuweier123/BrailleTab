#define MAIN_C
/*********************************************
Project : LCD TEST USE PB
Version :
Date : 2003-11-15
Author : Caijianqiang
Company :
Comments:
Chip type : ATMEGA8
Clock frequency : 8.000000 MHz
Memory model : Small
External SRAM size : 0
Data Stack size : 128
*********************************************/
#include "includes.h"
__flash unsigned char test1[]="Mega16 LCD test!";
__flash unsigned char test2[]="data use PORTB!";
__flash unsigned char test3[]="05/18/2005";
__flash unsigned char test4[]="write by MaChao";

// Declare your global variables here
unsigned char s[5];
void main(void)
{

// Declare your local variables here
// Port B initialization
// Func0=In Func1=In Func2=In Func3=In Func4=In Func5=In Func6=In Func7=In
// State0=T State1=T State2=T State3=T State4=T State5=T State6=T State7=T
PORTB=0x00;
DDRB=0x00;
// Port C initialization
// Func0=In Func1=In Func2=In Func3=In Func4=In Func5=In Func6=In Func7=In
// State0=T State1=T State2=T State3=T State4=T State5=T State6=T State7=T
PORTC=0x00;
DDRC=0x00;
// Port D initialization
// Func0=In Func1=In Func2=In Func3=In Func4=In Func5=In Func6=In Func7=In
// State0=T State1=T State2=T State3=T State4=T State5=T State6=T State7=T
PORTD=0x80;
DDRD=0x00;
// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;
// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
// Analog Comparator Output: Off
ACSR=0x80;
SFIOR=0x00;
// LCD module initialization
//delay_nms(50);
Init_LCD();
/*LCD_DisplayCharacter('a'); 
LCD_DisplayCharacter('b'); 
LCD_DisplayCharacter('c'); */
//init_usart();
//LCD_DisplayString_F(1,1,test1);
//LCD_DisplayString_F(2,1,test2);
//LCD_DisplayString_F(3,1,test3);
//s[0]='A';
//s[1]='B';
//s[2]='C';
//s[3]=0;
//LCD_DisplayString(4,11,s);
while (1)
 { 
   LCD_Clear();
   LCD_DisplayString_F(1,1,test1);
   delay_nms(1000);
   LCD_DisplayString_F(2,1,test2);
   delay_nms(1000); 
   LCD_Clear(); 
   LCD_DisplayString_F(1,1,test3);
   delay_nms(1000);
   LCD_DisplayString_F(2,1,test4);
   delay_nms(1000);
 //usart_putchar('a');
 //printf("Hello!\n");
 ;// Place your code here
 }
}

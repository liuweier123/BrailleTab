//ICC-AVR application builder : 2006-11-1 0:27:10
// Target : M32
// Crystal: 7.3728Mhz
//文件名：device_init.c 各种参数初始化
#include "config.h"

void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0x00; 
 PORTB = 0x00;
 DDRB  = 0x00; 
 PORTC = 0x00; 
 DDRC  = 0x00;
 PORTD = 0x00;
 DDRD  = 0xB0; // D7 PWM   //参考芯片手册
}

/**************************采用timer2 产生波形***********************/
// PWM频率 = 系统时钟频率/（分频系数*2*计数器上限值）） 
void timer2_init(void)
{
 TCCR2 = 0x00;  //stop
 TCNT2= 0x01;  //set count
 OCR2 = 0x66;  //set compare
 TCCR2 = (1<<WGM20)|(1<<WGM21)|(1<<COM21)|0x06; //  start timer 快速pwm模式，匹配清零，溢出置位 256分频
//占空比＝高比低为：(OCR2-0X01)/(0XFF-OCR2)    OX01++++++(OCR2)__________OXFF (+表示输出高，_表示输出低)
//即OCR2越大，输出越大
}

//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 port_init();
 timer2_init();
 TIMSK = 0x00; //timer interrupt sources
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}
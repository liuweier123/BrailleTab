#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>

void int1_init()
	{
	DDRD&=0x0f;
	PORTD|=0xf8;
	MCUCR|=(1<<ISC11);//上升沿触发
	MCUCR|=(1<<ISC10);
	GIFR|=(1<<INTF1);
	GICR|=(1<<INT1);	//int1开中断
	}
	
void pwm_init()
	{
	DDRB|=0b00000110;
	TCCR1A|=0b10100010;
	TCCR1B|=0b00011001;
	ICR1=0x7ff;
	OCR1A=0x7ff;
	OCR1B=0x400;
	}

void main()
	{
	int1_init();
	pwm_init();
	sei();
	}
	
INTERRUPT(SIG_INTERRUPT1)
	{
	OCR1A+=10;
	}

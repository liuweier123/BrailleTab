sbit LED= P1^4;				//LED light
sbit KEYLINE0 = P1^0;	  	//KEY
sbit KEYLINE1 = P1^1;
sbit KEYROW0 = P1^2;
sbit KEYROW1 = P1^3;

sbit LEDHIGH = P2^0;
sbit LEDLOW = P2^1;


#define TRUEFLAG 1
#define FALSEFLAG 0
#define KEYNULL 0xFF
#define KEYERR 0xF0

#define MAXLEN 38
#define UARTSOF 'a'
#define UARTEOF 'b'

#define LEDLEN 6

/*Display of LED
#define LED0	0x3F	//digital LED display digit of "0"
#define LED1	0x06	//digital LED display digit of "1"
#define LED2	0x5B	//digital LED display digit of "2"
#define LED3	0x4F	//digital LED display digit of "3"
#define LED4	0x66	//digital LED display digit of "4"
#define LED5	0x6D	//digital LED display digit of "5"
#define LED6	0x7D	//digital LED display digit of "6"
#define LED7	0x07	//digital LED display digit of "7"
#define LED8	0x7F	//digital LED display digit of "8"
#define LED9	0x6F	//digital LED display digit of "9"
#define LEDERR	0x79	//digital LED display digit of "E"
*/
#define LED0	0xFF-0x3F	//digital LED display digit of "0"
#define LED1	0xFF-0x06	//digital LED display digit of "1"
#define LED2	0xFF-0x5B	//digital LED display digit of "2"
#define LED3	0xFF-0x4F	//digital LED display digit of "3"
#define LED4	0xFF-0x66	//digital LED display digit of "4"
#define LED5	0xFF-0x6D	//digital LED display digit of "5"
#define LED6	0xFF-0x7D	//digital LED display digit of "6"
#define LED7	0xFF-0x07	//digital LED display digit of "7"
#define LED8	0xFF-0x7F	//digital LED display digit of "8"
#define LED9	0xFF-0x6F	//digital LED display digit of "9"
#define LEDERR	0xFF-0x79	//digital LED display digit of "E"

#define LEDSEG1	0xFF-0x01	//digital LED display digit of "1"
#define LEDSEG2	0xFF-0x02	//digital LED display digit of "2"
#define LEDSEG3	0xFF-0x04	//digital LED display digit of "3"
#define LEDSEG4	0xFF-0x08	//digital LED display digit of "4"
#define LEDSEG5	0xFF-0x10	//digital LED display digit of "5"
#define LEDSEG6	0xFF-0x20	//digital LED display digit of "6"
#define LEDSEG7	0xFF-0x40	//digital LED display digit of "7"


enum
{
	KEYON,
	KEYOFF,
	DISP1,
	DISP2,
	DISP3,
	DISP4,
	DISP5,
	DISP6
};
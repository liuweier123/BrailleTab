/* variable definition */
unsigned char data Timer10msFlag;
unsigned char data counter;
unsigned char data LEDTimer;
unsigned char data UartProFlag;
unsigned char data screenno;
unsigned char code welcome[]="please input the number(6 digits):\r\n";
unsigned char code menu[]="1.test           \r\n 2.test2          \r\n";
extern unsigned char data Keyflag; 
extern unsigned char data Leddata[LEDLEN];

extern unsigned char data UartReceBuf[MAXLEN];
extern unsigned char data UartRecePtr;
extern unsigned char data UartSendBuf[MAXLEN];
extern unsigned char data UartSendPtr;
extern unsigned char data UartSendFlag;
extern unsigned char data UartReceFlag;
extern unsigned char data UartSendTempPtr;

/* function declaration */
void Time500ms(void);
void UartRecePro(void);
void KeyPro(void);
void UartPro(void);
extern void MCUInit(void);
extern void SYSInit(void);
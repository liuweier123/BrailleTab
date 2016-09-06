/* variable definition */
unsigned char data Timer;
unsigned char data RollTimer;
unsigned char data Keystatus;
unsigned char data Key;
unsigned char data FormerKey;
unsigned char data Keyontimer;
unsigned char data Keyofftimer;
unsigned char data Keyflag;

unsigned char data Ledstatus;
unsigned char data Leddata[LEDLEN];


unsigned char data UartReceBuf[MAXLEN];
unsigned char data UartRecePtr;
unsigned char data UartSendBuf[MAXLEN];
unsigned char data UartSendPtr;
unsigned char data UartSendFlag;
unsigned char data UartReceFlag;
unsigned char data UartSendTempPtr;

extern unsigned char data Timer10msFlag;
/* function declaration */
void MCUInit(void);
void SYSInit(void);
unsigned char ChangeDisp(unsigned char leddata);
#include "at89x52.H"
#include "experiment.h"
#include "init.H"

/*************************************************************
*  FUNCTION NAME:void MCUInit(void)
*  PARAMETERS:
*  DESCRIPTION:intialize the SFR of MCU
*  RETURNS:
*  CREATED: XiongHui 2005-12-16 
*  HISTORY OF CHANGE: 
*************************************************************/
void MCUInit(void)
{
	TMOD = 0x21;		//timer control mode
	TH0 = 0xF6; 		//2.5ms for AT89S52, system clock is 11.092MHz
	TL0 = 0x00;
	TH1 = 0xFD; 		// 9600 Bds at 11.059MHz */
	TL1 = 0xFD; 		// 9600 Bds at 11.059MHz */
	PCON = 0x00;
	SCON = 0x50;		//serial communication control
	IP   = 0x00;
	TCON = 0x50;
	TI   = 0;
	RI   = 0;
	REN  = 1;			//enable serial uart's interruption
	IE   = 0x12;
	ES = 1; 			// Enable serial interrupt*/
	TR1 = 1; 			// Timer 1 run */
}
/*************************************************************
*  FUNCTION NAME:void MCUInit(void)
*  PARAMETERS:
*  DESCRIPTION:intialize the SFR of MCU
*  RETURNS:
*  CREATED: XiongHui 2005-12-16 
*  HISTORY OF CHANGE: 
*************************************************************/
void SYSInit(void)
{
	unsigned char i;
	Timer10msFlag = FALSEFLAG;
	Keyontimer = 0x0;
	Keyofftimer = 0x0;
	FormerKey = KEYNULL;
	Keystatus = KEYOFF;
	Key = KEYNULL;
	Keyflag = FALSEFLAG;
	for(i=0;i<LEDLEN;i++)
	{
	    Leddata[i] = i;
	 }

}
/*************************************************************
*  FUNCTION NAME:void Timer25msISR(void) interrupt  1
*  PARAMETERS:
*  DESCRIPTION:ISR of 2.5ms MCU timer0's interruption
*  RETURNS:
*  CREATED: XiongHui 2005-12-16 
*  HISTORY OF CHANGE: 
*************************************************************/
void Timer25msISR(void)  interrupt 1 using 2
{
	//unsigned char data i,mdata;
	TH0 = 0xF6; 						//2.5ms for AT89S52, system clock is 11.092MHz
	TL0 = 0x00;
	if(++Timer >= 4)					//timing for 10ms
	{
		Timer = 0;						//reset the value to zero
		Timer10msFlag = TRUEFLAG;
		/*
		if(++RollTimer >= 25)
		{
			mdata = Leddata[0];
			for(i=0;i<LEDLEN-1;i++)
			{
				Leddata[i] =  Leddata[i+1];
			}
			Leddata[LEDLEN-1] = mdata;
			RollTimer = 0x00;
		} */
	}
	switch(Ledstatus)
	{
		case DISP1:
			P2 = LEDSEG1;
			P0 = ChangeDisp(Leddata[0]);
			Ledstatus = DISP2;
			break;
		case DISP2:
			P2 = LEDSEG2;
			P0 = ChangeDisp(Leddata[1]);
			Ledstatus = DISP3;
			break;
		case DISP3:
			P2 = LEDSEG3;
			P0 = ChangeDisp(Leddata[2]);
			Ledstatus = DISP4;
			break;
		case DISP4:
			P2 = LEDSEG4;
			P0 = ChangeDisp(Leddata[3]);
			Ledstatus = DISP5;
			break;
		case DISP5:
			P2 = LEDSEG5;
			P0 = ChangeDisp(Leddata[4]);
			Ledstatus = DISP6;
			break;
		case DISP6:
			P2 = LEDSEG6;
			P0 = ChangeDisp(Leddata[5]);
			Ledstatus = DISP1;
			break;
		default:
			Ledstatus = DISP1;
			break;
	
	}
	
	Key = P1 & 0x0F;
	if(Key == 0x0F)
	{
		Key = KEYNULL;
	}
	else if(Key == 0x07 || Key == 0x0B || Key == 0x0D || Key == 0x0E)
	{
	
	}
	else
	{
		Key = KEYERR;
	}
	switch(Keystatus)
	{
		case KEYON:			 		//the status of key is "pushed"
			if(Key == KEYNULL)
			{
				if(++Keyontimer >= 20)
				{
					Keystatus = KEYOFF;
					Keyontimer = 0x0;
					Keyofftimer = 0x0;
				}
			}
			else
			{
				Keyontimer = 0x0;	
			}
			break;
	  	case KEYOFF:	  			//the status of key is "poped"
			if(Key == FormerKey && Key != KEYNULL)
			{
				if(++Keyofftimer >= 20)
				{
					Keystatus = KEYON;
					Keyontimer = 0x0;
					Keyofftimer = 0x0;
					Keyflag = TRUEFLAG;
					//Key	= Key;
				}
			}
			else
			{
				FormerKey = Key;
				Keyofftimer = 0x0;
			}	
			break;
	 	default:
			;
	
	}
}
/*************************************************************
*  FUNCTION NAME:void ChangeDisp(void) 
*  PARAMETERS:
*  DESCRIPTION:ISR of 2.5ms MCU timer0's interruption
*  RETURNS:
*  CREATED: XiongHui 2005-12-16 
*  HISTORY OF CHANGE: 
*************************************************************/
unsigned char ChangeDisp(unsigned char data leddata) using 2
{
	unsigned char data m;
	switch(leddata)
	{
		case 0:
			m =  LED0;
		   	break;
		case 1:
			m = LED1;
		   	break;
		case 2:
			m = LED2;
		   	break;
		case 3:
			m = LED3;
		   	break;
		case 4:
			m = LED4;
		   	break;
		case 5:
			m = LED5;
		   	break;
		case 6:
			m = LED6;
		   	break;
		case 7:
			m = LED7;
		   	break;
		case 8:
			m = LED8;
		   	break;
		case 9:
			m = LED9;
		   	break;
		default:
			m = LEDERR;
		   	break;
	}
	return m;
}
/*************************************************************
*  FUNCTION NAME:void UartISR(void) interrupt  4
*  PARAMETERS:
*  DESCRIPTION:ISR of MCU's Uart with external PC through RS485
*  RETURNS:
*  CREATED: XiongHui 2005-12-16 
*  HISTORY OF CHANGE: 
*************************************************************/
void UartISR(void) interrupt  4
{
	unsigned char data mdata;
	if(RI == 1)					      //here means that serial port received a byte
	{
    	RI = 0;                       //clear the status flag
		mdata = SBUF;
		SBUF = mdata;
		UartReceBuf[UartRecePtr++] = mdata;
		if(mdata == '\n' || UartReceBuf[UartRecePtr-1]=='\r')         //if received the end flag
		{
			UartReceFlag = TRUEFLAG;	//set the flag, then process the data frame reveived in the main loop program
		}
		else if(mdata == '\b')
		{
			UartRecePtr--;
			UartReceBuf[UartRecePtr--] = 0x00;	
		}

	}
    if(TI == 1)								//ISR for sending interruption
    {
    	TI=0;				//clear the flag
		if(UartSendFlag == TRUEFLAG)			    //sending flag
		{
			if(UartSendBuf[UartSendTempPtr-2]=='\r' || UartSendBuf[UartSendTempPtr-1] == '\n')	//compare the sending pointer and the temp pointer to judge whether the data have been sent over
			{
				UartSendTempPtr = 0;				//
                UartSendPtr = 0;
                UartSendFlag = FALSEFLAG;
			}
			else
			{
				SBUF = UartSendBuf[UartSendTempPtr++];	    	//send the data left
			}
		 }
    }
}
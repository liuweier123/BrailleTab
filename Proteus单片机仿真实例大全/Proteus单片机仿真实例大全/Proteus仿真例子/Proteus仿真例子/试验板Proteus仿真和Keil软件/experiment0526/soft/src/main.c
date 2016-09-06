#include <intrins.h>
#include <string.h>
#include "at89x52.H"
#include "experiment.h"
#include "main.h"
#define LEDNULL 1
#define LEDADD 1
/*************************************************************
*  FUNCTION NAME:Main(void)
*  PARAMETERS:
*  DESCRIPTION:main function
*  RETURNS:
*  CREATED: XiongHui 2006-3-18 
*  HISTORY OF CHANGE: 
*************************************************************/
void main(void)
{
	EA = 0;
	MCUInit();				//initialize the SFR of MCU 
	SYSInit();				//read the Variables of system
	EA = 1;					//enable the global interrupt flag
	UartProFlag = TRUEFLAG;
	while(1)
	{
		Time500ms();
		KeyPro();
		UartRecePro();
		UartPro();
	}
}
/********************************************************************************
*  FUNCTION NAME:Time500ms(void)
*  PARAMETERS:key
*  DESCRIPTION:time delay  		  
*  RETURNS:
*  CREATED: XiongHui 2006-3-18 
*  HISTORY OF CHANGE: 
*********************************************************************************/
void Time500ms(void)
{
	
	if(Timer10msFlag == TRUEFLAG)
	{
		Timer10msFlag = FALSEFLAG;
		if(++counter >= 50)
		{
			LED = !LED;
			counter = 0;  
		
		}
		
	}
}
/********************************************************************************
*  FUNCTION NAME:KeyPro(void)
*  PARAMETERS:key
*  DESCRIPTION:time delay  		  
*  RETURNS:
*  CREATED: XiongHui 2006-3-18 
*  HISTORY OF CHANGE: 
*********************************************************************************/
void KeyPro(void)
{
	if(Keyflag == TRUEFLAG)
	{
		Keyflag = FALSEFLAG;
		#ifndef LEDADD
		if(++Leddata[0] >= 10)
		{
			Leddata[0] = 0x0;	
		}
		if(++Leddata[1] >= 10)
		{
			Leddata[1] = 0x0;	
		}
		#else
		
		if(++Leddata[5] >= 10)
		{
			Leddata[5] = 0x0;
			if(++Leddata[4] >= 10)
			{
				Leddata[4] = 0x0;
				if(++Leddata[3] >= 10)
				{
					Leddata[3] = 0x0;
					if(++Leddata[2] >= 10)
					{
						Leddata[2] = 0x0;
						if(++Leddata[1] >= 10)
						{
							Leddata[1] = 0x0;
							if(++Leddata[0] >= 10)
							{
								Leddata[0] = 0x0;
								
									
							}	
						}
							
					}	
				}
					
			}	
		}

		#endif
	}
}
/********************************************************************************
*  FUNCTION NAME:UartRecePro(void)
*  PARAMETERS:key
*  DESCRIPTION:time delay  		  
*  RETURNS:
*  CREATED: XiongHui 2006-3-18 
*  HISTORY OF CHANGE: 
*********************************************************************************/
void UartRecePro(void)
{
	unsigned char data *codeptr;
	unsigned char data *dataptr;
	unsigned char data i,buf[6];
	codeptr = &UartReceBuf[0];
	dataptr	= &buf[0];
	if(UartReceFlag == TRUEFLAG)
	{
		UartReceFlag = FALSEFLAG;
		switch(screenno)
		{
			case 0:
				UartSendPtr = 0;
				//UartSendBuf[UartSendPtr++] = 'O';
				//UartSendBuf[UartSendPtr++] = 'K';
				UartSendBuf[UartSendPtr++] = '\r';
				UartSendBuf[UartSendPtr++] = '\n';
				strcpy(dataptr,codeptr);
				for(i=0;i<6;i++)
				{
					Leddata[i]= buf[i]-0x30;
				}

				UartSendTempPtr = 0x00;
				UartSendFlag = TRUEFLAG; 
				screenno=0;
				while(TI==0);
				SBUF = UartSendBuf[UartSendTempPtr++];						//intiates the sending
				break;
			case 1:
				UartSendPtr = 0;
				UartSendBuf[UartSendPtr++] = 'g';
				UartSendBuf[UartSendPtr++] = 'o';
				UartSendBuf[UartSendPtr++] = 'o';
				UartSendBuf[UartSendPtr++] = 'd';
				UartSendBuf[UartSendPtr++] = '\r';
				UartSendBuf[UartSendPtr++] = '\n';
				UartSendTempPtr = 0x00;
				UartSendFlag = TRUEFLAG;
				screenno=0;
				TI = 1;						//intiates the sending
				break;
			 default:
			 	;
	
		}
		UartRecePtr =0x00;
	}
}
/********************************************************************************
*  FUNCTION NAME:UartRecePro(void)
*  PARAMETERS:key
*  DESCRIPTION:time delay  		  
*  RETURNS:
*  CREATED: XiongHui 2006-3-18 
*  HISTORY OF CHANGE: 
*********************************************************************************/
void UartPro(void)
{
    unsigned char code *codeptr;
	unsigned char data *dataptr;
	if(UartProFlag == TRUEFLAG)
	{
		UartProFlag = FALSEFLAG;
		codeptr = &welcome[0];
		dataptr	= &UartSendBuf[0];
		strcpy(dataptr,codeptr);
		UartSendTempPtr = 0x00;
		UartSendFlag = TRUEFLAG;
		screenno = 0;
		TI = 1;						//intiates the sending
	}
}
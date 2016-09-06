
#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

/*
*********************************************************************************************************
*                                DELAY TASK 'n' TICKS   (n from 0 to 65535)
*
* Description: This function is called to delay execution of the currently running task until the 
*              specified number of system ticks expires.  This, of course, directly equates to delaying
*              the current task for some time to expire.  No delay will result If the specified delay is 
*              0.  If the specified delay is greater than 0 then, a context switch will result.
*
* Arguments  : ticks     is the time delay that the task will be suspended in number of clock 'ticks'.  
*                        Note that by specifying 0, the task will not be delayed.
*
* Returns    : none
*********************************************************************************************************
*/

void OSTimeDly (INT16U ticks)
{
    if (ticks > 0) {                                                      /* 0 means no delay!         */
        OS_ENTER_CRITICAL();
        if ((OSRdyTbl[OSTCBCur->OSTCBY] &= ~OSTCBCur->OSTCBBitX) == 0) {  /* Delay current task        */
            OSRdyGrp &= ~OSTCBCur->OSTCBBitY;
        }
        OSTCBCur->OSTCBDly = ticks;                                       /* Load ticks in TCB         */
        OS_EXIT_CRITICAL();
        OSSched();                                                        /* Find next task to run!    */
    }
}
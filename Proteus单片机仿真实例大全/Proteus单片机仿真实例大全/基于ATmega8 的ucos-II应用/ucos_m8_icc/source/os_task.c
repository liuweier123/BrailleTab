
#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                            CREATE A TASK
*
* Description: This function is used to have uC/OS-II manage the execution of a task.  Tasks can either
*              be created prior to the start of multitasking or by a running task.  A task cannot be
*              created by an ISR.
*
* Arguments  : task     is a pointer to the task's code
*
*              pdata    is a pointer to an optional data area which can be used to pass parameters to
*                       the task when the task first executes.  Where the task is concerned it thinks
*                       it was invoked and passed the argument 'pdata' as follows:
*
*                           void Task (void *pdata)
*                           {
*                               for (;;) {
*                                   Task code;
*                               }
*                           }
*
*              ptos     is a pointer to the task's top of stack.  If the configuration constant 
*                       OS_STK_GROWTH is set to 1, the stack is assumed to grow downward (i.e. from high
*                       memory to low memory).  'pstk' will thus point to the highest (valid) memory 
*                       location of the stack.  If OS_STK_GROWTH is set to 0, 'pstk' will point to the 
*                       lowest memory location of the stack and the stack will grow with increasing
*                       memory locations.
*
*              prio     is the task's priority.  A unique priority MUST be assigned to each task and the
*                       lower the number, the higher the priority.
*
* Returns    : OS_NO_ERR        if the function was successful.
*              OS_PRIO_EXIT     if the task priority already exist 
*                               (each task MUST have a unique priority).
*              OS_PRIO_INVALID  if the priority you specify is higher that the maximum allowed 
*                               (i.e. >= OS_LOWEST_PRIO)
*********************************************************************************************************
*/

#if OS_TASK_CREATE_EN
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt){

    INT8U  *stk;
    INT8U  *stks;		// Temp. variable used for setting up AVR hardware stack
    INT16U tmp;


    opt     = opt;			// 'opt' is not used, prevent warning
    stk     = (INT8U *)ptos;		// Wandlung von ptos in Bytezeiger
	// AVR return stack ("hardware stack")
    stks    = (INT8U *)(ptos)-(OS_TASK_DEF_STK_SIZE-32);

	// the function address has an extra level of indirection. Fetch the
    // actual address.
    //    
    tmp = *(INT16U const *)task;
   
	// 36 Bytes
    *stks-- = (INT8U)tmp;	//Put task start address on top of hardware stack
    *stks-- = (INT8U)(tmp >> 8);

    *stk-- = (INT8U)0x00;		// R0  = 0x00
    *stk-- = (INT8U)0x01; 
    *stk-- = (INT8U)0x02;
    *stk-- = (INT8U)0x03;
    *stk-- = (INT8U)0x04;
    *stk-- = (INT8U)0x05;
    *stk-- = (INT8U)0x06;
    *stk-- = (INT8U)0x07;
    *stk-- = (INT8U)0x08;
    *stk-- = (INT8U)0x09;
    *stk-- = (INT8U)0x10;
    *stk-- = (INT8U)0x11;
    *stk-- = (INT8U)0x12;
    *stk-- = (INT8U)0x13;
    *stk-- = (INT8U)0x14;
    *stk-- = (INT8U)0x15;
    tmp    = (INT16U)pdata;
    *stk-- = (INT8U)tmp;	//Simulate call to function with argument
    *stk-- = (INT8U)(tmp >> 8);
    *stk-- = (INT8U)0x18;
    *stk-- = (INT8U)0x19;
    *stk-- = (INT8U)0x20;
    *stk-- = (INT8U)0x21;
    *stk-- = (INT8U)0x22;
    *stk-- = (INT8U)0x23;
    *stk-- = (INT8U)0x24;
    *stk-- = (INT8U)0x25;
    *stk-- = (INT8U)0x26;
    *stk-- = (INT8U)0x27;
	// the heap pointer Y=R29:R28 will not be stored
    *stk-- = (INT8U)0x30;
    *stk-- = (INT8U)0x31;
//    *stk-- = (INT8U)0x3B;
    *stk-- = (INT8U)0x80;	//SREG = Interrupts enabled

    tmp    = (INT16U)(stks);
    *stk-- = (INT8U)(tmp >> 8);
    *stk   = (INT8U)(tmp);
    return ((void *)stk);
}

INT8U OSTaskCreate (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT8U prio)
{
    void   *psp;
    INT8U   err;


    if (prio > OS_LOWEST_PRIO) {             /* Make sure priority is within allowable range           */
        return (OS_PRIO_INVALID);
    }
    OS_ENTER_CRITICAL();
    if (OSTCBPrioTbl[prio] == (OS_TCB *)0) { /* Make sure task doesn't already exist at this priority  */
        OSTCBPrioTbl[prio] = (OS_TCB *)1;    /* Reserve the priority to prevent others from doing ...  */
                                             /* ... the same thing until task is created.              */
        OS_EXIT_CRITICAL();
        psp = (void *)OSTaskStkInit(task, pdata, ptos, 0); /* Initialize the task's stack              */
        err = OSTCBInit(prio, psp, (void *)0, 0, 0, (void *)0, 0);         
        if (err == OS_NO_ERR) {
            OS_ENTER_CRITICAL();
            OSTaskCtr++;                                   /* Increment the #tasks counter             */
            OS_EXIT_CRITICAL();
            if (OSRunning) {                 /* Find highest priority task if multitasking has started */
                OSSched();
            }
        } else {
            OS_ENTER_CRITICAL();
            OSTCBPrioTbl[prio] = (OS_TCB *)0;/* Make this priority available to others                 */
            OS_EXIT_CRITICAL();
        }
        return (err);
    } else {
        OS_EXIT_CRITICAL();
        return (OS_PRIO_EXIST);
    }
}
#endif
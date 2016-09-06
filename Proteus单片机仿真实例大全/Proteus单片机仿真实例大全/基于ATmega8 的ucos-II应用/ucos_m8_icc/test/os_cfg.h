/*
********************************************************************************
*                             uC/OS-II
*                         The Real-Time Kernel
*
*                     Configuration for ATmega103
*
* File:		OS_CFG.H
* By:			Ole Saether
* Modified by:	Joerg Meyer
* Revision:		0
*
********************************************************************************
*/

/*
********************************************************************************
*                       uC/OS-II CONFIGURATION
********************************************************************************
*/
// alle nachfolgenden parameter sind entsprechend der eigenen Applikation 
// anzupassen
// Default stack size (# of bytes)
#define OS_TASK_DEF_STK_SIZE	100
// Max. number of event control blocks in your application MUST be >= 2
#define OS_MAX_EVENTS		2	 
// Max. number of tasks in your application MUST be >= 2
#define OS_MAX_TASKS		5
// Defines the lowest priority that can be assigned MUST NEVER be higher than 63
#define OS_LOWEST_PRIO		15
// Idle task stack size
#define OS_TASK_IDLE_STK_SIZE OS_TASK_DEF_STK_SIZE
// Statistics task stack size
#define OS_TASK_STAT_STK_SIZE OS_TASK_DEF_STK_SIZE
// Include (1) or Exlude (0) code for OSTaskCreate()
#define OS_TASK_CREATE_EN		1

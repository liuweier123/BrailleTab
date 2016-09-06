/*
 *********************************************************************************************************
 *                                               uC/OS-II
 *                                         The Real-Time Kernel
 *
 *                                        ATmega103 Specific code
 *
 * File     : OS_CPU.H
 * By       : Ole Saether
 *
 * $Revision: 1 $
 *
 *********************************************************************************************************
*/

#include <macros.h>

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*
**********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
**********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                       /* Unsigned  8 bit quantity                         */
typedef signed   char  INT8S;                       /* Signed    8 bit quantity                         */
typedef unsigned int   INT16U;                      /* Unsigned 16 bit quantity                         */
typedef signed   int   INT16S;                      /* Signed   16 bit quantity                         */
typedef unsigned long  INT32U;                      /* Unsigned 32 bit quantity                         */
typedef signed   long  INT32S;                      /* Signed   32 bit quantity                         */
typedef float          FP32;                        /* Single precision floating point                  */

typedef unsigned char  OS_STK;                      /* Each stack entry is 8-bit wide                   */

/*
**********************************************************************************************************
*                                       Atmel AVR
*
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts. In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section. The IAR compiler does not support inline assembly so I'm
*             using the _OPC() intrinsic function. Here are the instructions:
*
*             OS_ENTER_CRITICAL:
*
*               ST      -Y,R16
*               IN      R16,SREG
*               CLI
*               PUSH    R16
*               LD      R16,Y+
*
*             OS_EXIT_CRITICAL:
*
*               ST      -Y,R16
*               POP     R16
*               OUT     SREG,R16
*               LD      R16,Y+
*
**********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    2

#if      OS_CRITICAL_METHOD == 1
#define  OS_ENTER_CRITICAL()    CLI()              /* Disable interrupts                               */
#define  OS_EXIT_CRITICAL()     SEI()              /* Enable  interrupts                               */
#endif

#if      OS_CRITICAL_METHOD == 2
#define  OS_ENTER_CRITICAL()    asm("st -y,r16\nin r16,0x3F\ncli\npush r16\nld r16,y+");
#define  OS_EXIT_CRITICAL()     asm("st -y,r16\npop r16\nout 0x3F,r16\nld r16,y+");
//#define  OS_EXIT_CRITICAL()     asm("st -y,r16\npop r16\nout 0x3F,r16\nsei\nld r16,y+");
//#define  OS_ENTER_CRITICAL()      CLI()
//#define  OS_EXIT_CRITICAL()       SEI()
#endif

/*
**********************************************************************************************************
*                           AVR Miscellaneous
**********************************************************************************************************
*/

#define  OS_STK_GROWTH      1                       /* Stack grows from HIGH to LOW memory on AVR       */

#define  OS_TASK_SW()       OSCtxSw()

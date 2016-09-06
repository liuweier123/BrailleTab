/*
*********************************************************************************************************
*                                             MISCELLANEOUS
*********************************************************************************************************
*/

#ifdef   OS_GLOBALS
#define  OS_EXT
#else
#define  OS_EXT  extern
#endif

#define  OS_PRIO_SELF           0xFF   /* Indicate SELF priority                                       */

#if      OS_TASK_STAT_EN
#define  OS_N_SYS_TASKS            2                    /* Number of system tasks                      */
#else
#define  OS_N_SYS_TASKS            1
#endif

#define  OS_STAT_PRIO       (OS_LOWEST_PRIO - 1)        /* Statistic task priority                     */
#define  OS_IDLE_PRIO       (OS_LOWEST_PRIO)            /* IDLE      task priority                     */

#define  OS_EVENT_TBL_SIZE ((OS_LOWEST_PRIO) / 8 + 1)   /* Size of event table                         */
#define  OS_RDY_TBL_SIZE   ((OS_LOWEST_PRIO) / 8 + 1)   /* Size of ready table                         */

#define  OS_TASK_IDLE_ID       65535   /* I.D. numbers for Idle and Stat tasks                         */
#define  OS_TASK_STAT_ID       65534

                                       /* TASK STATUS (Bit definition for OSTCBStat)                   */
#define  OS_STAT_RDY            0x00   /* Ready to run                                                 */
#define  OS_STAT_SEM            0x01   /* Pending on semaphore                                         */
#define  OS_STAT_MBOX           0x02   /* Pending on mailbox                                           */
#define  OS_STAT_Q              0x04   /* Pending on queue                                             */
#define  OS_STAT_SUSPEND        0x08   /* Task is suspended                                            */

#define  OS_EVENT_TYPE_MBOX        1
#define  OS_EVENT_TYPE_Q           2
#define  OS_EVENT_TYPE_SEM         3

                                       /* TASK OPTIONS (see OSTaskCreateExt())                         */
#define  OS_TASK_OPT_STK_CHK  0x0001   /* Enable stack checking for the task                           */
#define  OS_TASK_OPT_STK_CLR  0x0002   /* Clear the stack when the task is create                      */
#define  OS_TASK_OPT_SAVE_FP  0x0004   /* Save the contents of any floating-point registers            */


#ifndef  FALSE
#define  FALSE                     0
#endif

#ifndef  TRUE
#define  TRUE                      1
#endif

/*
*********************************************************************************************************
*                                              ERROR CODES
*********************************************************************************************************
*/

#define OS_NO_ERR                 0
#define OS_ERR_EVENT_TYPE         1
#define OS_ERR_PEND_ISR           2

#define OS_TIMEOUT               10
#define OS_TASK_NOT_EXIST        11

#define OS_PRIO_EXIST            40
#define OS_PRIO_ERR              41
#define OS_PRIO_INVALID          42

#define OS_TASK_DEL_ERR          60
#define OS_TASK_DEL_IDLE         61
#define OS_TASK_DEL_REQ          62
#define OS_TASK_DEL_ISR          63

#define OS_NO_MORE_TCB           70

#define OS_TIME_NOT_DLY          80
#define OS_TIME_INVALID_MINUTES  81
#define OS_TIME_INVALID_SECONDS  82
#define OS_TIME_INVALID_MILLI    83
#define OS_TIME_ZERO_DLY         84

#define OS_TASK_SUSPEND_PRIO     90
#define OS_TASK_SUSPEND_IDLE     91

#define OS_TASK_RESUME_PRIO     100
#define OS_TASK_NOT_SUSPENDED   101

#define OS_TASK_OPT_ERR         130

/*$PAGE*/
/*
*********************************************************************************************************
*                                          EVENT CONTROL BLOCK
*********************************************************************************************************
*/

#if (OS_MAX_EVENTS >= 2)
typedef struct {
    void   *OSEventPtr;                    /* Pointer to message or queue structure                    */
    INT8U   OSEventTbl[OS_EVENT_TBL_SIZE]; /* List of tasks waiting for event to occur                 */
    INT16U  OSEventCnt;                    /* Count of used when event is a semaphore                  */
    INT8U   OSEventType;                   /* OS_EVENT_TYPE_MBOX, OS_EVENT_TYPE_Q or OS_EVENT_TYPE_SEM */
    INT8U   OSEventGrp;                    /* Group corresponding to tasks waiting for event to occur  */
} OS_EVENT;
#endif

/*
*********************************************************************************************************
*                                            TASK STACK DATA
*********************************************************************************************************
*/

#if OS_TASK_CREATE_EXT_EN
typedef struct {
    INT32U  OSFree;                    /* Number of free bytes on the stack                            */
    INT32U  OSUsed;                    /* Number of bytes used on the stack                            */
} OS_STK_DATA;
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                          TASK CONTROL BLOCK
*********************************************************************************************************
*/

typedef struct os_tcb {
    OS_STK        *OSTCBStkPtr;        /* Pointer to current top of stack                              */

    struct os_tcb *OSTCBNext;          /* Pointer to next     TCB in the TCB list                      */
    struct os_tcb *OSTCBPrev;          /* Pointer to previous TCB in the TCB list                      */

    INT16U         OSTCBDly;           /* Nbr ticks to delay task or, timeout waiting for event        */
    INT8U          OSTCBStat;          /* Task status                                                  */
    INT8U          OSTCBPrio;          /* Task priority (0 == highest, 63 == lowest)                   */

    INT8U          OSTCBX;             /* Bit position in group  corresponding to task priority (0..7) */
    INT8U          OSTCBY;             /* Index into ready table corresponding to task priority        */
    INT8U          OSTCBBitX;          /* Bit mask to access bit position in ready table               */
    INT8U          OSTCBBitY;          /* Bit mask to access bit position in ready group               */
} OS_TCB;

/*$PAGE*/
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/
                                       
OS_EXT  INT32U       OSCtxSwCtr;               /* Counter of number of context switches                */

#if     (OS_MAX_EVENTS >= 2)
OS_EXT  OS_EVENT    *OSEventFreeList;          /* Pointer to list of free EVENT control blocks         */
OS_EXT  OS_EVENT     OSEventTbl[OS_MAX_EVENTS];/* Table of EVENT control blocks                        */
#endif

OS_EXT  INT32U       OSIdleCtr;                /* Idle counter                                         */

#if     OS_TASK_STAT_EN
OS_EXT  INT8S        OSCPUUsage;               /* Percentage of CPU used                               */
OS_EXT  INT32U       OSIdleCtrMax;             /* Maximum value that idle counter can take in 1 sec.   */
OS_EXT  INT32U       OSIdleCtrRun;             /* Value reached by idle counter at run time in 1 sec.  */
OS_EXT  BOOLEAN      OSStatRdy;                /* Flag indicating that the statistic task is ready     */
#endif

OS_EXT  INT8U        OSIntNesting;             /* Interrupt nesting level                              */

OS_EXT  INT8U        OSLockNesting;            /* Multitasking lock nesting level                      */

OS_EXT  INT8U        OSPrioCur;                /* Priority of current task                             */
OS_EXT  INT8U        OSPrioHighRdy;            /* Priority of highest priority task                    */

OS_EXT  INT8U        OSRdyGrp;                        /* Ready list group                              */
OS_EXT  INT8U        OSRdyTbl[OS_RDY_TBL_SIZE];       /* Table of tasks which are ready to run         */

OS_EXT  BOOLEAN      OSRunning;                       /* Flag indicating that kernel is running        */

#if     OS_TASK_CREATE_EN  || OS_TASK_CREATE_EXT_EN || OS_TASK_DEL_EN
OS_EXT  INT8U        OSTaskCtr;                       /* Number of tasks created                       */
#endif

OS_EXT  OS_TCB      *OSTCBCur;                        /* Pointer to currently running TCB              */
OS_EXT  OS_TCB      *OSTCBFreeList;                   /* Pointer to list of free TCBs                  */
OS_EXT  OS_TCB      *OSTCBHighRdy;                    /* Pointer to highest priority TCB ready to run  */
OS_EXT  OS_TCB      *OSTCBList;                       /* Pointer to doubly linked list of TCBs         */
OS_EXT  OS_TCB      *OSTCBPrioTbl[OS_LOWEST_PRIO + 1];/* Table of pointers to created TCBs             */

OS_EXT  INT32U       OSTime;                   /* Current value of system time (in ticks)              */


extern  INT8U const  OSMapTbl[];               /* Priority->Bit Mask lookup table                      */
extern  INT8U const  OSUnMapTbl[];             /* Priority->Index    lookup table                      */

/*$PAGE*/
/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*                                     (Target Independant Functions)
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            TASK MANAGEMENT
*********************************************************************************************************
*/

INT8U       OSTaskCreate(void (*task)(void *pd), void *pdata, OS_STK *ptos, INT8U prio);

/*
*********************************************************************************************************
*                                            TIME MANAGEMENT
*********************************************************************************************************
*/
void        OSTimeDly(INT16U ticks);
void        OSTimeTick(void);

/*
*********************************************************************************************************
*                                             MISCELLANEOUS
*********************************************************************************************************
*/

void        OSInit(void);

void        OSIntExit(void);

void        OSStart(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                      INTERNAL FUNCTION PROTOTYPES
*                            (Your application MUST NOT call these functions)
*********************************************************************************************************
*/

void        OSSched(void);

void        OSTaskIdle(void *data);

INT8U       OSTCBInit(INT8U prio, OS_STK *ptos, OS_STK *pbos, INT16U id, INT16U stk_size, void *pext, INT16U opt);

/*$PAGE*/
/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*                                      (Target Specific Functions)
*********************************************************************************************************
*/

void        OSCtxSw(void);

void        OSIntCtxSw(void);

void        OSStartHighRdy(void);

void        OSTickISR(void);

void        init164(void);
void        write164(unsigned char  x);
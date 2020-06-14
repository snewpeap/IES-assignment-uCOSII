/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 1998-2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                            WIN32 Sample Code
*
* File : APP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE    128
#define  TASK_START_PRIO    5
#define  COMPTIME_1    (INT16U)1 /*任务1运行时间，下同*/
#define  DEADLINE_1    (INT16U)4 /*任务1截止时间，下同*/
#define  COMPTIME_2    (INT16U)2
#define  DEADLINE_2    (INT16U)5
#define  COMPTIME_3    (INT16U)2
#define  DEADLINE_3    (INT16U)10
#define  DATA_SHARE_EN    1  /*是否运行在共享数据模式*/

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK        AppStartTaskStk[TASK_STK_SIZE];
OS_STK		  MyTaskStks[3][TASK_STK_SIZE];
static OS_EVENT	  *sem;

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void Task1(void *p_arg);
void Task2(void *p_arg);
void Task3(void *p_arg);

/*
*********************************************************************************************************
*                                                _tmain()
*
* Description : This is the standard entry point for C++ WIN32 code.  
* Arguments   : none
*********************************************************************************************************
*/

void main(int argc, char *argv[])
{
	INT8U err;

#if 0
    BSP_IntDisAll();                       /* For an embedded target, disable all interrupts until we are ready to accept them */
#endif

    OSInit();                              /* Initialize "uC/OS-II, The Real-Time Kernel"                                      */

#if DATA_SHARE_EN > 0
	printf("    Data sharing mode");
	sem = OSSemCreate(1);
#else
	printf("    Not data sharing mode");
#endif // DATA_SHARE_EN > 0

	MyOSTaskCreate(Task1, (void *)0, (OS_STK *)&MyTaskStks[0][TASK_STK_SIZE - 1], 1, COMPTIME_1, DEADLINE_1);
	MyOSTaskCreate(Task2, (void *)0, (OS_STK *)&MyTaskStks[1][TASK_STK_SIZE - 1], 2, COMPTIME_2 ,DEADLINE_2);
	MyOSTaskCreate(Task3, (void *)0, (OS_STK *)&MyTaskStks[2][TASK_STK_SIZE - 1], 3, COMPTIME_3 ,DEADLINE_3);

#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (INT8U *)"Start Task", &err);
#endif

#if OS_TASK_NAME_SIZE > 14
    OSTaskNameSet(OS_IDLE_PRIO, (INT8U *)"uC/OS-II Idle", &err);
#endif

#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_STAT_PRIO, "uC/OS-II Stat", &err);
#endif

    OSStart();                             /* Start multitasking (i.e. give control to uC/OS-II)                               */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

void Task1(void *p_arg) {
	p_arg = p_arg;
	INT8U err;

	int start, end, toDelay, pended = 1;
	start = 0;
	while (1) {
#if DATA_SHARE_EN > 0
		if (OSTCBCur->OSTCBPrio == 3) {
			pended = 0;
			while (OSSemAccept(sem));
		} else if (OSTCBCur->OSTCBPrio == 1) {
			pended = 0;
			OSSemPend(sem, 0, &err);
		}
#endif
		while (OSTCBCur->CompTime>0) {
			/* Do nothing but wasting time */
		}
		end = OSTimeGet();
		toDelay = DEADLINE_1 - (end - start);
		start += DEADLINE_1;
		OSTCBCur->CompTime = COMPTIME_1;
		OSTCBCur->Deadline += DEADLINE_1;
#if DATA_SHARE_EN > 0
		if (pended == 0) {
			pended = 1;
			OSSemPost(sem);
		}
#endif // DATA_SHARE_EN > 0
		OSTimeDly(toDelay);
	}
}

void Task2(void *p_arg) {
	p_arg = p_arg;
	INT8U err;

	int start, end, toDelay, pended = 1;
	start = 0;
	while (1) {
#if DATA_SHARE_EN > 0
		if (OSTCBCur->OSTCBPrio == 3) {
			pended = 0;
			while (OSSemAccept(sem));
		} else if (OSTCBCur->OSTCBPrio == 1) {
			pended = 0;
			OSSemPend(sem, 0, &err);
		}
#endif
		while (OSTCBCur->CompTime > 0) {
			/* Do nothing but wasting time */
		}
		end = OSTimeGet();
		toDelay = DEADLINE_2 - (end - start);
		start += DEADLINE_2;
		OSTCBCur->CompTime = COMPTIME_2;
		OSTCBCur->Deadline += DEADLINE_2;
#if DATA_SHARE_EN > 0
		if (pended == 0) {
			pended = 1;
			OSSemPost(sem);
		}
#endif // DATA_SHARE_EN > 0
		OSTimeDly(toDelay);
	}
}

void Task3(void *p_arg) {
	p_arg = p_arg;
	INT8U err;

	int start, end, toDelay, pended = 1;
	start = 0;
	while (1) {
#if DATA_SHARE_EN > 0
		if (OSTCBCur->OSTCBPrio == 3) {
			pended = 0;
			while (OSSemAccept(sem));
		} else if (OSTCBCur->OSTCBPrio == 1) {
			pended = 0;
			OSSemPend(sem, 0, &err);
		}
#endif
		while (OSTCBCur->CompTime > 0) {
			/* Do nothing but wasting time */
		}
		end = OSTimeGet();
		toDelay = DEADLINE_3 - (end - start);
		start += DEADLINE_3;
		OSTCBCur->CompTime = COMPTIME_3;
		OSTCBCur->Deadline += DEADLINE_3;
#if DATA_SHARE_EN > 0
		if (pended == 0) {
			pended = 1;
			OSSemPost(sem);
		}
#endif // DATA_SHARE_EN > 0
		OSTimeDly(toDelay);
	}
}

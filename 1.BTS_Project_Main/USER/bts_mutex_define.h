#ifndef __MUTEX_DEFINE__
#define __MUTEX_DEFINE__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------(SEMAPHORE SYS ALL)-----------------------------------*/
typedef struct
{
	xSemaphoreHandle Lock_SendChar;
	xSemaphoreHandle Lock_Queue;
}mutexSysList_t;

/*-----------------------------------(SEMAPHORE SYS ALL)-----------------------------------*/
typedef struct
{
	xSemaphoreHandle Lock_Queue;
}mutexIOList_t;

/*-----------------------------------(SEMAPHORE SYS ALL)-----------------------------------*/
typedef struct
{
	xSemaphoreHandle Lock_Queue;
}mutexUARTList_t;


/*-----------------------------------(SEMAPHORE LIST ALL)-----------------------------------*/
typedef struct
{
	mutexSysList_t SYS;
	mutexIOList_t IO;
	mutexUARTList_t UART;
}mutexListValue_t;


#ifdef __cplusplus
}
#endif

#endif

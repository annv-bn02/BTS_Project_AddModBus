#ifndef __QUEUE_DEFINE__
#define __QUEUE_DEFINE__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*-----------------------------------(QUEUE LIST TASK SYS TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Device;
}queueSysToUart_t;

typedef struct
{
	queueSysToUart_t To_Uart;
}queueSysTo_t;

/*-----------------------------------(QUEUE LIST TASK IO TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Device;
}queueIOToUart_t;

typedef struct
{
	xQueueHandle Queue_Device;
}queueIOToSys_t;

typedef struct
{
	queueIOToSys_t 	To_Sys;
	queueIOToUart_t To_Uart;
}queueIOTo_t;

/*-----------------------------------(QUEUE LIST TASK UART TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Device;
}queueUartToIo_t;

typedef struct
{
	xQueueHandle Queue_Device;
}queueUartToSys_t;

typedef struct
{
	queueUartToSys_t 	To_Sys;
	queueUartToIo_t 	To_Io;
}queueUartTo_t;

/*-----------------------------------(QUEUE LIST TASK FLASH TO )-----------------------------------*/
typedef struct
{
	xQueueHandle Queue_Slave_Id;
}queueFlashToIo_t;

typedef struct
{
	xQueueHandle Queue_Slave_Id;
}queueFlashToSys_t;

typedef struct
{
	xQueueHandle Queue_Slave_Id;
}queueFlashToUart_t;

typedef struct
{
	queueFlashToSys_t 	To_Sys;
	queueFlashToIo_t 	To_Io;
	queueFlashToUart_t 	To_Uart;
}queueFlashTo_t;

/*-----------------------------------(QUEUE LIST ALL)-----------------------------------*/
typedef struct
{
	queueSysTo_t  Sys;
	queueUartTo_t Uart;
	queueIOTo_t IO;
	queueFlashTo_t Flash;
}queueListValue_t;

#ifdef __cplusplus
}
#endif

#endif

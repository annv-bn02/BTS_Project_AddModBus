#ifndef __EVENT_DEFINE__
#define __EVENT_DEFINE__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

/*-----------------------------------(EVENT LIST TASK SYS TO )-----------------------------------*/
typedef struct
{
	EventGroupHandle_t EventGroup;
	uint8_t EventBit_FlagHasData;
	uint8_t EventBit_FlagHasDataUpdate;
}eventSysToUart_t;

typedef struct
{
	EventGroupHandle_t EventGroup;
	uint8_t EventBit_FlagHasData;
}eventSysToIO_t;

typedef struct
{
	eventSysToUart_t 	To_Uart;
	eventSysToIO_t 		To_IO;
}eventSysTo_t;

/*-----------------------------------(EVENT LIST TASK UART TO )-----------------------------------*/
typedef struct
{
	EventGroupHandle_t EventGroup;
	uint8_t EventBit_FlagHasData;
}eventUartToSys_t;

typedef struct
{
	eventUartToSys_t To_Sys;
}eventUartTo_t;

/*-----------------------------------(EVENT LIST TASK IO TO )-----------------------------------*/
typedef struct
{
	EventGroupHandle_t EventGroup;
	uint8_t EventBit_FlagHasData;
	uint8_t EventBit_FlagHasDataUpdate;
}eventIOToSys_t;

typedef struct
{
	eventIOToSys_t To_Sys;
}eventIOTo_t;

/*-----------------------------------(EVENT LIST ALL)-----------------------------------*/
typedef struct
{
	eventSysTo_t  Sys;
	eventUartTo_t Uart;
	eventIOTo_t IO;
}eventListValue_t;

#ifdef __cplusplus
}
#endif

#endif

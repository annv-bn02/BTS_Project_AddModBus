#include "bts_sys.h"
#include <stdarg.h>

volatile eventListValue_t EventTask1, EventTask2;
volatile mutexListValue_t MutexTask;
volatile queueListValue_t QueueTask;

void BTS_Sys_SendChar(char data);
void BTS_Sys_SendString(char *text);

/**
 * @brief Config for event of system.
 * 
 */
void BTS_Sys_EventInit(void)
{
	EventTask1.Sys.To_Uart.EventGroup 				 = xEventGroupCreate();
	EventTask1.Sys.To_Uart.EventBit_FlagHasData 		 = (1<<0);
	EventTask1.Sys.To_Uart.EventBit_FlagHasDataUpdate = (2<<0);
	
	EventTask1.Sys.To_IO.EventGroup 					 = xEventGroupCreate();
	EventTask1.Sys.To_IO.EventBit_FlagHasData 		 = (1<<0);
	
	EventTask1.Uart.To_Sys.EventGroup 				 = xEventGroupCreate();
	EventTask1.Uart.To_Sys.EventBit_FlagHasData 		 = (1<<0);
	
	EventTask1.IO.To_Sys.EventGroup 					 = xEventGroupCreate();
	EventTask1.IO.To_Sys.EventBit_FlagHasData 		 = (1<<0);
	EventTask1.IO.To_Sys.EventBit_FlagHasDataUpdate   = (2<<0);
	
	EventTask2.Flash.To_Sys.EventGroup 				 = xEventGroupCreate();
	EventTask2.Flash.To_Sys.EventBit_SlaveID 			 = (1<<0);
	
	EventTask2.Sys.To_Uart.EventGroup 				 = xEventGroupCreate();
	EventTask2.Sys.To_Uart.EventBit_SlaveID		 = (1<<0);
}

/**
 * @brief Config for mutex of system.
 * 
 */
void BTS_Sys_MutexInit(void)
{
	MutexTask.SYS.Lock_SendChar = xSemaphoreCreateMutex();
	MutexTask.IO.Lock_Queue 	= xSemaphoreCreateMutex();
	MutexTask.UART.Lock_Queue   = xSemaphoreCreateMutex();
}

/**
 * @brief Config for queue of system.
 * 
 */
void BTS_Sys_QueueInit(void)
{
	QueueTask.Flash.To_Uart.Queue_Slave_Id 	= xQueueCreate(10, sizeof(flashInformation_t));
	QueueTask.Uart.To_Io.Queue_Device 	  	= xQueueCreate(10, sizeof(controlDeviceFrame_t));
	QueueTask.IO.To_Uart.Queue_Device 	  	= xQueueCreate(10, sizeof(updateDeviceFrame_t));
}

/**
 * @brief Config for utilities of system.
 * 
 */
void BTS_Sys_Init(void)
{
	BTS_Sys_MutexInit();
	BTS_Sys_EventInit();
	BTS_Sys_QueueInit();
}

/**
 * @brief Send data debug to the debug screen.
 * same as printf() function in c language.
 * @param format : array format of data debug
 * @param ... 
 */
void BTS_Sys_Debug(const char *format, ...) 
{
	char arr[20];
	va_list args;
	va_start(args, format);
	while (*format != '\0') 
	{
		if (*format == '%') 
		{
			format++;
			switch (*format)
			{
				case 'd':
					sprintf(arr, "%d", va_arg(args, int));
					BTS_Sys_SendString(arr);
					break;
				case 's':
					sprintf(arr, "%s", va_arg(args, char *));
					BTS_Sys_SendString(arr);
					break;
				case 'f':
					sprintf(arr, "%0.1lf", va_arg(args, double));
					BTS_Sys_SendString(arr);
					break;
				case 'x':
					sprintf(arr, "%x", va_arg(args, int));
					BTS_Sys_SendString(arr);
					break;
				default:
					BTS_Sys_SendString("printf error!!!\n");
					break;
			}
		} 
		else 
		{
		  BTS_Sys_SendChar(*format);
		}
		format++;
	}
	va_end(args);
}

/**
 * @brief Send error debug to the debug screen.
 * 
 * @param error : name of error.
 */
void BTS_Debug_Error(uint8_t* error)
{
	BTS_Sys_Debug("----------------(Error: %s )--------------", error);
}

/**
 * @brief Send char to the screen debug.
 * 
 * @param data : char to send.
 */
void BTS_Sys_SendChar(char data)
{
	xSemaphoreTake(MutexTask.SYS.Lock_SendChar, portMAX_DELAY);
	SmartBTS_USART0_SendChar((uint8_t)data);
	xSemaphoreGive(MutexTask.SYS.Lock_SendChar);
}

/**
 * @brief Send string to the screen debug.
 * 
 * @param text : array of chars to send.
 */
void BTS_Sys_SendString(char *text)
{
	while(*text)
	{
		BTS_Sys_SendChar((uint8_t)*text);
		text++;
	}
}


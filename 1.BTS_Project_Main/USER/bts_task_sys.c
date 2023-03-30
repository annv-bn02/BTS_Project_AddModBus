#include "bts_task_sys.h"


static void SendEventControl_SysToIo(void);
static void SendEventUpdate_SysToUart(void);
static void SendEventControl_SysToUart(void);
static void SendEventSlaveID_SysToUart(void);
static void GetEventUpdate_IoToSys(EventBits_t event);
static void GetEventControl_IoToSys(EventBits_t event);
static void GetEventControl_UartToSys(EventBits_t event);
static void GetEventSlaveID_FlashToSys(EventBits_t event);

/**
 * @brief System Task funtion of RTOS system
 * 
 * @param p 
 */
void BTS_RTOS_Task_SYS(void *p)
{
	EventBits_t event;
	while(1)
	{
		GetEventUpdate_IoToSys(event);
		GetEventControl_IoToSys(event);
		GetEventControl_UartToSys(event);
		GetEventSlaveID_FlashToSys(event);
		uartDataHandler();
		Modbus_Counter();
		vTaskDelay(TIME_DELAY_TASK_SYS/portTICK_RATE_MS);
	}
	
}

/**
 * @brief Send event control device from system task to io task
 * 
 */
static void SendEventControl_SysToIo(void)
{
	xEventGroupSetBits(EventTask1.Sys.To_IO.EventGroup, EventTask1.Sys.To_IO.EventBit_FlagHasData);
}

/**
 * @brief Send event update data of device and sensor from system task to transmission task
 * 
 */
static void SendEventUpdate_SysToUart(void)
{
	xEventGroupSetBits(EventTask1.Sys.To_Uart.EventGroup, EventTask1.Sys.To_Uart.EventBit_FlagHasDataUpdate);
}

/**
 * @brief Send event control device from system task to transmission task
 * 
 */
static void SendEventControl_SysToUart(void)
{
	xEventGroupSetBits(EventTask1.Sys.To_Uart.EventGroup, EventTask1.Sys.To_Uart.EventBit_FlagHasData);
}

static void SendEventSlaveID_SysToUart(void)
{
	xEventGroupSetBits(EventTask2.Sys.To_Uart.EventGroup, EventTask2.Sys.To_Uart.EventBit_SlaveID);
}

/**
 * @brief Get event update data of device and sensor from IO task to system task
 * 
 */
static void GetEventUpdate_IoToSys(EventBits_t event)
{
	//If SYS has event from IO, SYS sends event to UART 
	event = xEventGroupWaitBits(EventTask1.IO.To_Sys.EventGroup, EventTask1.IO.To_Sys.EventBit_FlagHasDataUpdate, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask1.IO.To_Sys.EventBit_FlagHasDataUpdate)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Event Update IO to SYSTEM done\n");
#endif
		SendEventUpdate_SysToUart();
	}
}

/**
 * @brief Get event control device from IO task to system task
 * 
 */
static void GetEventControl_IoToSys(EventBits_t event)
{
	//If SYS has event from IO, SYS sends event to UART 
	event = xEventGroupWaitBits(EventTask1.IO.To_Sys.EventGroup, EventTask1.IO.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask1.IO.To_Sys.EventBit_FlagHasData)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Event Control IO to SYSTEM done\n");
#endif
		SendEventControl_SysToUart();
	}
}

/**
 * @brief Get event control device from transmission task to system task
 * 
 * @param event 
 */
static void GetEventControl_UartToSys(EventBits_t event)
{
	//If SYS has event from UART, SYS sends event to IO 
	event = xEventGroupWaitBits(EventTask1.Uart.To_Sys.EventGroup, EventTask1.Uart.To_Sys.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask1.Uart.To_Sys.EventBit_FlagHasData)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Event Control UART to SYSTEM done\n");
#endif
		SendEventControl_SysToIo();
	}
}

static void GetEventSlaveID_FlashToSys(EventBits_t event)
{
	event = xEventGroupWaitBits(EventTask2.Flash.To_Sys.EventGroup, EventTask2.Flash.To_Sys.EventBit_SlaveID, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask2.Flash.To_Sys.EventBit_SlaveID)
	{
		SendEventSlaveID_SysToUart();
	}
}

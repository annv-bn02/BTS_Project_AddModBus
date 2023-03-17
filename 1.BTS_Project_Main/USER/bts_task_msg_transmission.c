#include "bts_task_msg_transmission.h"

#define DEBUG_CREATE_CONTROL_DEVICE 0
#define DEBUG_CREATE_MESSAGE_UPDATE_DEVICE 0
#define DEBUG_CREATE_MESSAGE_UPDATE_SENSOR 0

static void GetNewMessage(void);
static void GetQueueDevice_IoToUart(void);
static void GetQueueSensor_IoToUart(void);
static void SendEventControl_UartToSys(void);
static void GetEventUpdate_SysToUart(EventBits_t event);
static void GetEventControl_SysToUart(EventBits_t event);
static void SendQueue_UartToIO(const uint8_t name, const uint8_t value);
//	Function Test
static void CreateControlDeviceTest(const uint8_t name, const uint8_t value);
static void CreateMessageUpdateDeviceTest(void);
static void CreateMessageUpdateSensorTest(void);

uint32_t counter_control = 0;

/**
 * @brief Transmission task funtion of RTOS system
 * 
 * @param p 
 */
void BTS_RTOS_Task_Msg(void *p)
{
	EventBits_t event;
#if DEBUG_CREATE_CONTROL_DEVICE
	CreateControlDeviceTest(2,255); 
#endif
	
#if DEBUG_CREATE_MESSAGE_UPDATE_DEVICE
	CreateMessageUpdateDeviceTest(); 
#endif
	
#if DEBUG_CREATE_MESSAGE_UPDATE_SENSOR
	CreateMessageUpdateSensorTest(); 
#endif
	
	while(1)
	{
		GetNewMessage();
		GetEventUpdate_SysToUart(event);
		GetEventControl_SysToUart(event);
		vTaskDelay(TIME_DELAY_TASK_MSG/portTICK_RATE_MS);
	}
}

/**
 * @brief Get the New Message control device
 * When the new message control device come, detect it and send name device and value of device to IO Task.
 */
static void GetNewMessage(void)
{
	uint16_t lenght = 0;
	uint8_t* array_data;
	uint8_t size_array_data = 0;
	messageFrameMsg_t frame_message;
	if(Is_Message(&lenght) != 0)
	{
		if(lenght > 0)
		{
			array_data = SmartBTS_USART3_Get_Array_Data();
			size_array_data = DetectMessage(array_data, &frame_message);
#if DEBUG_TASK_MSG_NEW_MESSAGE
			DebugMessage(array_data);
#endif
			if(size_array_data > 0)
			{
				if(frame_message.TypeMessage == TYPE_MESSAGE_CONTROL_DEVICE)
				{
					SendQueue_UartToIO(frame_message.Data[0], frame_message.Data[1]);
					SendEventControl_UartToSys();
				}
			}
		}
	}
	Time_Out_Get_Message();
}

/**
 * @brief Get the data of devices for update from IO Task
 * When the data devices come, creat frame array bytes of data and send it.
 */
static void GetQueueDevice_IoToUart(void)
{
	uint8_t count = 0, size_data = 0;
	uint8_t array_data_update_device[DEFAULT_MAX_NUMBER_DEVICE], array_data_out[50];
	updateDeviceFrame_t frame_update_device;
	xSemaphoreTake(MutexTask.UART.Lock_Queue, portMAX_DELAY);
	if(xQueueReceive(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_device, TIME_WAIT_QUEUE))
	{
		for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
		{
			array_data_update_device[count] = frame_update_device.data[count];
		}
		size_data = BTS_Frame_Creat_Device(array_data_update_device, array_data_out);
#if DEBUG_TASK_MSG_CREATE_MESSAGE_DEVICE
		DebugMessage(array_data_out);
#endif
		SmartBTS_USART3_SendArrayByte(array_data_out, size_data);
	}
	xSemaphoreGive(MutexTask.UART.Lock_Queue);
}

/**
 * @brief Get the data of sensors for update from IO Task
 * When the data sensors come, creat frame array bytes of data and send it.
 */
static void GetQueueSensor_IoToUart(void)
{
	uint8_t count = 0, size_data = 0;
	uint8_t array_data_out[50];
	float array_data_update_sensor[DEFAULT_MAX_NUMBER_SENSOR];
	updateSensorFrame_t frame_update_sensor;
	xSemaphoreTake(MutexTask.UART.Lock_Queue, portMAX_DELAY);
	if(xQueueReceive(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_sensor, TIME_WAIT_QUEUE))
	{
		for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
		{
			array_data_update_sensor[count] = frame_update_sensor.data[count];
		}
		size_data = BTS_Frame_Creat_Sensor(array_data_update_sensor, array_data_out);
#if DEBUG_TASK_MSG_CREATE_MESSAGE_SENSOR
		DebugMessage(array_data_out);
#endif
		SmartBTS_USART3_SendArrayByte(array_data_out, size_data);
	}
	xSemaphoreGive(MutexTask.UART.Lock_Queue);
}

/**
 * @brief Send event control device to sys task.
 * 
 */
static void SendEventControl_UartToSys(void)
{
	xEventGroupSetBits(EventTask.Uart.To_Sys.EventGroup, EventTask.Uart.To_Sys.EventBit_FlagHasData);	
	
}

/**
 * @brief Get event update data of device and sensor from sys task.
 * 
 */
static void GetEventUpdate_SysToUart(EventBits_t event)
{
	//If UART has event from SYS, end event progress;
	event = xEventGroupWaitBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasDataUpdate, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Sys.To_Uart.EventBit_FlagHasDataUpdate)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Update\n");
#endif	
		GetQueueDevice_IoToUart();
		GetQueueSensor_IoToUart();
#if DEBUG_ALL
		BTS_Sys_Debug("End Update\n\n");
#endif	
	}
}

/**
 * @brief Get event control data of device and sensor from sys task.
 * 
 */
static void GetEventControl_SysToUart(EventBits_t event)
{
	//If UART has event from SYS, end event progress;
	event = xEventGroupWaitBits(EventTask.Sys.To_Uart.EventGroup, EventTask.Sys.To_Uart.EventBit_FlagHasData, pdTRUE, pdFALSE, TIME_WAIT_EVENT_ALL);
	if(event & EventTask.Sys.To_Uart.EventBit_FlagHasData)
	{
#if DEBUG_ALL
		BTS_Sys_Debug("Event Control SYSTEM to UART done\n");
#endif
//		GetQueueDevice_IoToUart();
//		GetQueueSensor_IoToUart();
		counter_control++;
#if DEBUG_ALL
		BTS_Sys_Debug("End test\n\n");
#endif
	}
}
/**
 * @brief Send name device and value control to IO task
 * 
 * @param name : name of device
 * @param value : value control device
 */

static void SendQueue_UartToIO(const uint8_t name, const uint8_t value)
{
	controlDeviceFrame_t data_frame;
	data_frame.name = name;
	data_frame.value = value;
	xSemaphoreTake(MutexTask.UART.Lock_Queue, portMAX_DELAY);
	xQueueSend(QueueTask.Uart.To_Io.Queue_Device, (void *)&data_frame, TIME_WAIT_QUEUE);
	xSemaphoreGive(MutexTask.UART.Lock_Queue);
}

/**
 * @brief Create a Control Device Test object
 * Test object is used to create a control device message.
 * @param name : name of device
 * @param value : value control device
 */
static void CreateControlDeviceTest(const uint8_t name, const uint8_t value)
{
	uint8_t array_control[50];
	uint8_t size_array = 0, count = 0;
	BTS_Sys_Debug("\n---------------(Create Control Device Test)---------------");
	size_array = BTS_Frame_Control_Device(name,value,array_control);
	BTS_Sys_Debug("\n---------------(Size : %d)---------------\n", size_array);
	for(count = 0; count < size_array; count++)
	{
		if(array_control[count] <= 0x0f)
		{
			BTS_Sys_Debug("0%x ", array_control[count]);
		}
		else
		{
			BTS_Sys_Debug("%x ", array_control[count]);
		}
	}
	BTS_Sys_Debug("---------------(Done)---------------\n");
}

/**
 * @brief Create a Message Update Device Test object
 * Test object is used to create a update device message.
 */
static void CreateMessageUpdateDeviceTest(void)
{
	uint8_t array_data_in[DEFAULT_MAX_NUMBER_DEVICE], array_data_out[50];
	uint8_t size_array = 0, count = 0;
	for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
	{
		array_data_in[count] = count;
	}
	BTS_Sys_Debug("\n---------------(Create Message Update Device Test)---------------");
	size_array = BTS_Frame_Creat_Device(array_data_in, array_data_out);
	BTS_Sys_Debug("\n---------------(Size : %d)---------------\n", size_array);
	for(count = 0; count < size_array; count++)
	{
		if(array_data_out[count] <= 0x0f)
		{
			BTS_Sys_Debug("0%x ", array_data_out[count]);
		}
		else
		{
			BTS_Sys_Debug("%x ", array_data_out[count]);
		}
	}
	DebugMessage(array_data_out);
	BTS_Sys_Debug("---------------(Done)---------------\n");
}

/**
 * @brief Create a Message Update Sensor Test object
 * Test object is used to create a update sensor message.
 */
static void CreateMessageUpdateSensorTest(void)
{
	uint8_t array_data_out[50];
	float array_data_in[DEFAULT_MAX_NUMBER_SENSOR];
	uint8_t size_array = 0, count = 0;
	for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
	{
		array_data_in[count] = 20.5 + count;
	}
	BTS_Sys_Debug("\n---------------(Create Message Update Sensor Test)---------------");
	size_array = BTS_Frame_Creat_Sensor(array_data_in, array_data_out);
	BTS_Sys_Debug("\n---------------(Size : %d)---------------\n", size_array);
	for(count = 0; count < size_array; count++)
	{
		if(array_data_out[count] <= 0x0f)
		{
			BTS_Sys_Debug("0%x ", array_data_out[count]);
		}
		else
		{
			BTS_Sys_Debug("%x ", array_data_out[count]);
		}
	}
	DebugMessage(array_data_out);
	BTS_Sys_Debug("---------------(Done)---------------\n");
}

#include "bts_task_msg_transmission.h"

static void GetQueueDevice_IoToUart(void);
static void GetQueueSensor_IoToUart(void);
static void SendEventControl_UartToSys(void);
static void GetEventUpdate_SysToUart(EventBits_t event);
static void GetEventControl_SysToUart(EventBits_t event);
static void SendQueue_UartToIO(const uint8_t name, const uint8_t value);

#if DEBUG_DATA_SENSOR_REGISTER
static void Debug_Data_Register_Sensor(void); 
#endif
#if DEBUG_DATA_DEVICE_REGISTER
static void Debug_Data_Register_Device(void);
#endif
uint32_t counter_control = 0;
/**
 * @brief Transmission task funtion of RTOS system
 * 
 * @param p 
 */
void BTS_RTOS_Task_Msg(void *p)
{
	uint16_t control_data;
	uint8_t *data_control;
	EventBits_t event;
	while(1)
	{
		control_data = Control_Data_Flag();
		GetEventUpdate_SysToUart(event);
		GetEventControl_SysToUart(event);
		if(control_data != 0)
		{
			SendEventControl_UartToSys();
			data_control = Bts_Convert_From_Uint16_To_Bytes(control_data);
			SendQueue_UartToIO(data_control[0], data_control[1]);
		}
		vTaskDelay(TIME_DELAY_TASK_MSG/portTICK_RATE_MS);
	}
}

/**
 * @brief Get the data of devices for update from IO Task
 * When the data devices come, creat frame array bytes of data and send it.
 */
static void GetQueueDevice_IoToUart(void)
{
	uint8_t count = 0;
	uint8_t array_data_update_device[DEFAULT_MAX_NUMBER_DEVICE];
	uint8_t device_number;
	updateDeviceFrame_t frame_update_device;
	xSemaphoreTake(MutexTask.UART.Lock_Queue, portMAX_DELAY);
	if(xQueueReceive(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_device, TIME_WAIT_QUEUE))
	{
		for(count = 0; count < DEFAULT_MAX_NUMBER_DEVICE; count++)
		{
			array_data_update_device[count] = frame_update_device.data[count];
		}
		for(count = REGISTER_ADDRESS_DEVICE_START; count <= REGISTER_ADDRESS_DEVICE_END; count++)
		{
			device_number = (count - 20) * 2;
			bts_modbus_register[count] = Bts_Convert_From_Bytes_To_Uint16(array_data_update_device[device_number + 1], array_data_update_device[device_number]);
		}
#if DEBUG_DATA_DEVICE_REGISTER
		Debug_Data_Register_Device();
#endif
	}
	xSemaphoreGive(MutexTask.UART.Lock_Queue);
}

/**
 * @brief Get the data of sensors for update from IO Task
 * When the data sensors come, creat frame array bytes of data and send it.
 */
static void GetQueueSensor_IoToUart(void)
{
	uint8_t count = 0;
	uint8_t sensor_number;
	float array_data_update_sensor[DEFAULT_MAX_NUMBER_SENSOR];
	updateSensorFrame_t frame_update_sensor;
	xSemaphoreTake(MutexTask.UART.Lock_Queue, portMAX_DELAY);
	if(xQueueReceive(QueueTask.IO.To_Uart.Queue_Device, (void *)&frame_update_sensor, TIME_WAIT_QUEUE))
	{
		for(count = 0; count < DEFAULT_MAX_NUMBER_SENSOR; count++)
		{
			array_data_update_sensor[count] = frame_update_sensor.data[count];
		}
		for(count = REGISTER_ADDRESS_SENSOR_START; count <= REGISTER_ADDRESS_SENSOR_END; count += 2)
		{
			static data_format_float_Uint16 input_convert; 
			sensor_number = count / 2;
			input_convert.data_float = array_data_update_sensor[sensor_number];
			bts_modbus_register[count] = input_convert.uint16[1];
			bts_modbus_register[count + 1] = input_convert.uint16[0];
		}
#if DEBUG_DATA_SENSOR_REGISTER
		Debug_Data_Register_Sensor();
#endif
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

#if DEBUG_DATA_SENSOR_REGISTER
static void Debug_Data_Register_Sensor(void)
{
	int count;
	BTS_Sys_Debug("\n-------------------REGISTER SENSOR-----------------\n");
	for(count = REGISTER_ADDRESS_SENSOR_START; count <= REGISTER_ADDRESS_SENSOR_END; count ++)
	{
		BTS_Sys_Debug("Register %d = %x\n", count, bts_modbus_register[count]);
	}
	BTS_Sys_Debug("\n----------------END REGISTER SENSOR----------------\n");
}
#endif
#if DEBUG_DATA_DEVICE_REGISTER
static void Debug_Data_Register_Device(void)
{
	int count;
	BTS_Sys_Debug("\n-------------------REGISTER DEVICE-----------------\n");
	for(count = REGISTER_ADDRESS_DEVICE_START; count <= REGISTER_ADDRESS_DEVICE_END; count++)
	{
		BTS_Sys_Debug("Register %d = %x\n", count, bts_modbus_register[count]);
	}
	BTS_Sys_Debug("\n----------------END REGISTER DEVICE----------------\n");
}
#endif

#ifndef __SYS__
#define __SYS__
	
#ifdef __cplusplus
extern "C"{
#endif

#include "gd32f30x.h"
#include "gd32f30x_gpio.h"
#include "gd32f30x_eval.h"
#include "gd32f30x_adc.h"

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "croutine.h"
#include "event_groups.h"
#include "stream_buffer.h"
#include "string.h"
#include "math.h"

#include "bts_uart.h"
#include "bts_uart3.h"
#include "bts_task_io.h"
#include "bts_task_sys.h"
#include "bts_task_msg_transmission.h"
#include "bts_adc.h"

#include "bts_event_define.h"
#include "bts_mutex_define.h"
#include "bts_queue_define.h"

#include "bts_convert.h"
#include "bts_config_gpio.h"

#include "bts_automatic_control.h"
#include "bts_device.h"

#include "bts_sensor_airconditioner.h"
#include "bts_sensor_smoke.h"
#include "bts_sensor_door.h"
#include "bts_sensor_ntc.h"
#include "bts_sensor_water.h"

#include "bts_modbus_slave.h"

extern volatile eventListValue_t EventTask;
extern volatile mutexListValue_t MutexTask;
extern volatile queueListValue_t QueueTask;

#define RETRUN_ERROR -1

#define DEFAULT_MAX_NUMBER_SENSOR               10          							//  support max 10 sensors
#define DEFAULT_MAX_NUMBER_DEVICE               (DEFAULT_MAX_NUMBER_SENSOR*4)          	//  support max 40 device

#define TIME_DELAY_TASK_MSG 	1
#define TIME_DELAY_TASK_IO 		1
#define TIME_DELAY_TASK_SYS 	1

#define TIME_WAIT_EVENT_ALL		0
#define TIME_WAIT_QUEUE			(portTickType)0

#define COUNTER_UPDATE_DATA 		100 	
#define COUNTER_SMOKE_WARNING 		20 	
#define COUNTER_TIMEOUT 			20 	

#define DEBUG_ALL 								0
#define DEBUG_DATA_SENSOR_REGISTER 				0
#define DEBUG_DATA_DEVICE_REGISTER 				0
#define DEBUG_ERROR 							0

#define REGISTER_ADDRESS_SENSOR_START	0	
#define REGISTER_ADDRESS_SENSOR_END		19
#define REGISTER_ADDRESS_DEVICE_START	20
#define REGISTER_ADDRESS_DEVICE_END		39
/**
 * @brief structure of data for control device 
 * 
 */
typedef struct
{
	uint8_t name;
	uint8_t value;
}controlDeviceFrame_t;

/**
 * @brief structure of data for update device 
 * 
 */
typedef struct
{
	uint8_t data[DEFAULT_MAX_NUMBER_DEVICE];
}updateDeviceFrame_t;

/**
 * @brief structure of data for update sensor 
 * 
 */
typedef struct
{
	float data[DEFAULT_MAX_NUMBER_SENSOR];
}updateSensorFrame_t;
	

void BTS_Sys_EventInit(void);
void BTS_Sys_Init(void);

void BTS_Sys_MutexInit(void);
void BTS_Sys_QueueInit(void);
void BTS_Debug_Error(uint8_t* error);
void BTS_Sys_Debug(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

#ifndef __SYS__
#define __SYS__
	
#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdint.h>
#include "bts_convert.h"
#include "bts_frame_message.h"
#include "bts_get_message.h"
#include "bts_config_gpio.h"


#define DEBUG_ALL 0

#define TIME_DELAY_TASK_MSG 	1
#define TIME_DELAY_TASK_IO 		1
#define TIME_DELAY_TASK_SYS 	1

#define TIME_WAIT_EVENT_ALL		0
#define TIME_WAIT_QUEUE			(portTickType)0

#define COUNTER_UPDATE_DATA 		1000 	

#define COUNTER_SMOKE_WARNING 		100 	

#define COUNTER_TIMEOUT 	20 	

#define DEBUG_TASK_MSG_NEW_MESSAGE 0
#define DEBUG_TASK_MSG_CREATE_MESSAGE_DEVICE 0
#define DEBUG_TASK_MSG_CREATE_MESSAGE_SENSOR 0

#ifdef __cplusplus
}
#endif

#endif

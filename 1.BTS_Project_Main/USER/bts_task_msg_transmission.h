#ifndef __MSG_TRANSMISSION__
#define __MSG_TRANSMISSION__
	
#ifdef __cplusplus
extern "C"{
#endif
#include "bts_sys.h"

uint8_t Modbus_Slave_ID(void);
void BTS_RTOS_Task_Msg(void *p);

#ifdef __cplusplus
}
#endif

#endif

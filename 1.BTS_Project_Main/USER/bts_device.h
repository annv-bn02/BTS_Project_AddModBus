#ifndef _DEVICE_
#define _DEVICE_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

extern uint8_t array_data_device[40];

void BTS_Device_Init(void);
void BTS_Device_Control(uint8_t name_device, bit_status status);

#ifdef __cplusplus
}
#endif

#endif

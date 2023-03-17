#ifndef _AIRCONDITIONER_SENSOR_
#define _AIRCONDITIONER_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_AirCondition_Init(void);
uint8_t Sensor_AirCondition_Get(void);

#ifdef __cplusplus
}
#endif

#endif

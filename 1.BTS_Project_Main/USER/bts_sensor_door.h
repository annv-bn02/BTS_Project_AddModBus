#ifndef _DOOR_SENSOR_
#define _DOOR_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_Door_Init(void);
uint8_t Sensor_Door_Get(void);

#ifdef __cplusplus
}
#endif

#endif

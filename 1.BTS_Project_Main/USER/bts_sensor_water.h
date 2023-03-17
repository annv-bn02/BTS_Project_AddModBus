#ifndef _WATER_SENSOR_
#define _WATER_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_Water_Init(void);
uint8_t Sensor_Water_Get(void);

#ifdef __cplusplus
}
#endif

#endif

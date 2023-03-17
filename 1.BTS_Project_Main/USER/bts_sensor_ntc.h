#ifndef _NTC_SENSOR_
#define _NTC_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

void Sensor_NTC_Init(void);
void Sensor_NTC_Get(void);
extern float temperature_NTC1, temperature_NTC2;
#ifdef __cplusplus
}
#endif

#endif

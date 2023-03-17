#ifndef _SMOKE_SENSOR_
#define _SMOKE_SENSOR_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"

extern float smoke_flag;

void Sensor_Smoke_Init(void);
void Sensor_Smoke_Get(void);

#ifdef __cplusplus
}
#endif

#endif

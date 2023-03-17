#ifndef _AUTOMATIC_CONTROL_
#define _AUTOMATIC_CONTROL_

#ifdef __cplusplus
    extern "C" {
#endif

#include "bts_sys.h"


uint8_t bts_automatic_control_Door(uint8_t data_sensor);
uint8_t bts_automatic_control_Smoke(uint8_t data_sensor);
uint8_t bts_automatic_control_Fan_AirCondition(uint8_t data_sensor);

#ifdef __cplusplus
}
#endif

#endif

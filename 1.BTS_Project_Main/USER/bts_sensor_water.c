#include "bts_sensor_water.h"

/**
 * @brief Config the water sensor.
 * 
 */
void Sensor_Water_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_WATER);
}

uint8_t Sensor_Water_Get(void)
{
	return 1;
}

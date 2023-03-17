#include "bts_sensor_smoke.h"

float smoke_flag = 0;
uint16_t count_smoke_stt = 0;
uint16_t count_smoke_normal = 0;
uint16_t arr[1000];
/**
 * @brief Config the smoke sensor.
 * 
 */
void Sensor_Smoke_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_SMOKE);
}	

/**
 * @brief Get the smoke sensor status.
 * 
 * 
 */
void Sensor_Smoke_Get(void)
{
	if(gpio_input_bit_get(gpio_pin_sensor[SENSOR_SMOKE].port, gpio_pin_sensor[SENSOR_SMOKE].pin) == 1)
	{
		count_smoke_stt++;
		if(count_smoke_stt >= COUNTER_SMOKE_WARNING)
		{
			count_smoke_stt = 0;
			smoke_flag = 1;
#if DEBUG_ALL
			BTS_Sys_Debug("Smoke\n");
#endif
		}
	}
	else
	{
		count_smoke_stt = 0;
	}

}

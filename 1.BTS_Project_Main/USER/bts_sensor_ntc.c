#include "bts_sensor_ntc.h"

float temperature_NTC1, temperature_NTC2;
uint16_t counter_NTC = 0;
static float convert_NTC_Analog_to_Temperature(uint16_t adc_value);

/**
 * @brief Config for the sensor NTC.
 * 
 */
void Sensor_NTC_Init(void)
{
	BTS_Config_GPIO_Sensor(SENSOR_NTC1);
	BTS_Config_GPIO_Sensor(SENSOR_NTC2);
	BTS_ADC_NTC_Init();
}

/**
 * @brief Get temperature value of the sensor NTC.
 * 
 */
void Sensor_NTC_Get(void)
{	
	uint16_t adc_kalman;
	counter_NTC++;
	adc_software_trigger_enable(ADC1, ADC_INSERTED_CHANNEL);
	adc_kalman = ADC_Kalman_Filter(ADC_IDATA0(ADC1), &Kalman_NTC1);
	temperature_NTC1 = convert_NTC_Analog_to_Temperature(adc_kalman);
	
	adc_kalman = ADC_Kalman_Filter(ADC_IDATA1(ADC1), &Kalman_NTC2);
	temperature_NTC2 = convert_NTC_Analog_to_Temperature(adc_kalman);
	
#if DEBUG_ALL
	if(counter_NTC == 10000)
	{
		counter_NTC = 0;
		BTS_Sys_Debug("NTC 1: %d C\r\n", (int)(temperature_NTC1 * 100));
		BTS_Sys_Debug("NTC 2: %d C\r\n\n", (int)(temperature_NTC2 * 100));
	}
	BTS_Sys_Debug("\r\n ***********************************\r\n");
#endif

}

/**
 * @brief convert analog value of NTC to temerature value.
 * 
 * @param adc_value : analog value of NTC.
 * @return float : temperature value of NTC.
 */
static float convert_NTC_Analog_to_Temperature(uint16_t adc_value)
{
	float B = 3950, t0 = 298.15, r25 = 10000, v_out, r_ntc, v_supply = 3.3;
	float t;
	v_out =	adc_value * v_supply / 4095;
	r_ntc = (v_out * r25) /(v_supply - v_out);
	t = (t0*B)/(t0*log(r_ntc/r25)+B) - 273.15;    
	return t; 	
}

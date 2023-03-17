#ifndef __ADC__
#define __ADC__
	
#ifdef __cplusplus
extern "C"{
#endif
#include "bts_sys.h"

typedef struct
{
	float ADC_OLD_Value;
	float P_k1_k1;

	float Q;
	float R; 
	float Kg;
	float P_k_k1;
	float kalman_adc_old;
	
	uint8_t init_data;
}_adc_kalman_filter_t_;
extern _adc_kalman_filter_t_ Kalman_NTC1, Kalman_NTC2;

void BTS_ADC_NTC_Init(void);
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, _adc_kalman_filter_t_ *_adc_kalman_);	

#ifdef __cplusplus
}
#endif

#endif

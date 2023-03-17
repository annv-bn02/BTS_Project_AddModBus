
#include "bts_adc.h"
_adc_kalman_filter_t_ Kalman_NTC1, Kalman_NTC2;

/**
 * @brief Confiure the adc channel for read NTC analog data voltage
 * 
 * @param gpio_element : the position of the gpio element in the structure gpio_pin_sensor
 */
void BTS_ADC_NTC_Init(void)
{

/* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC1);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);
    /* ADC SCAN function enable */
    adc_special_function_config(ADC1, ADC_SCAN_MODE, ENABLE);
    adc_special_function_config(ADC1, ADC_CONTINUOUS_MODE, DISABLE); 
    /* ADC trigger config */
    adc_external_trigger_source_config(ADC1, ADC_INSERTED_CHANNEL, ADC0_1_2_EXTTRIG_INSERTED_NONE);
    /* ADC mode config */
    adc_mode_config(ADC_MODE_FREE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC1, ADC_DATAALIGN_RIGHT);  
    /* ADC channel length config */
    adc_channel_length_config(ADC1, ADC_INSERTED_CHANNEL, 2);

  
    /* ADC temperature sensor channel config */
    adc_inserted_channel_config(ADC1, 0, ADC_CHANNEL_0, ADC_SAMPLETIME_239POINT5);
    /* ADC internal reference voltage channel config */
    adc_inserted_channel_config(ADC1, 1, ADC_CHANNEL_1, ADC_SAMPLETIME_239POINT5);

    adc_external_trigger_config(ADC1, ADC_INSERTED_CHANNEL, ENABLE);
  
    /* ADC temperature and Vrefint enable */
    adc_tempsensor_vrefint_enable();
 
    
    /* enable ADC interface */
    adc_enable(ADC1);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC1);

}

/**
 * @brief Anti-interference for the analog voltage 
 * 
 * @param ADC_Value : analog voltage value
 * @param _adc_kalman_ : structure for the kalman filter
 * @return uint16_t : analog voltage after filtering
 */
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, _adc_kalman_filter_t_ *_adc_kalman_)
{
		float x_k1_k1,x_k_k1;
		uint16_t kalman_adc;
	  float Z_k;
		if(_adc_kalman_->init_data == 0)
		{
			_adc_kalman_->ADC_OLD_Value = 0.0;
			_adc_kalman_->P_k1_k1 = 0.0;
			_adc_kalman_->kalman_adc_old=0;
			_adc_kalman_->Q = 0.0001; //Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
			_adc_kalman_->R = 0.0005;    //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
			_adc_kalman_->Kg = 0;
			_adc_kalman_->P_k_k1 = 1;
			_adc_kalman_->init_data = 1;
		}
		
    Z_k = ADC_Value;
    x_k1_k1 = _adc_kalman_->kalman_adc_old;

    x_k_k1 = x_k1_k1;
    _adc_kalman_->P_k_k1 = _adc_kalman_->P_k1_k1 + _adc_kalman_->Q;

    _adc_kalman_->Kg = _adc_kalman_->P_k_k1/(_adc_kalman_->P_k_k1 + _adc_kalman_->R);

    kalman_adc = x_k_k1 + _adc_kalman_->Kg * (Z_k - _adc_kalman_->kalman_adc_old);
    _adc_kalman_->P_k1_k1 = (1 - _adc_kalman_->Kg)*_adc_kalman_->P_k_k1;
    _adc_kalman_->P_k_k1 = _adc_kalman_->P_k1_k1;

    _adc_kalman_->ADC_OLD_Value = ADC_Value;
    _adc_kalman_->kalman_adc_old = kalman_adc;
	return kalman_adc;
}

#include "bts_config_gpio.h"

#define NOT_USE_ADC 0

/**
 * @brief structure of gpio pin configuration for sensors.
 * 
 */
define_GpioPin_t gpio_pin_sensor[SIZE_LIST_SENSOR]=
{
	{GPIOA, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_0, ADC_CHANNEL_0,  "NTC1 Pin"},
	{GPIOA, GPIO_MODE_AIN,    GPIO_OSPEED_MAX,   GPIO_PIN_1, ADC_CHANNEL_1,  "NTC2 Pin"},	
	{GPIOA, GPIO_MODE_IPD,    GPIO_OSPEED_50MHZ, GPIO_PIN_14, NOT_USE_ADC,  "Door Pin"},
	{GPIOC, GPIO_MODE_IPD,    GPIO_OSPEED_50MHZ, GPIO_PIN_4, NOT_USE_ADC, "Smoke Pin"},
	{GPIOA, GPIO_MODE_IPD,    GPIO_OSPEED_50MHZ, GPIO_PIN_15, NOT_USE_ADC, "Water Pin"},
	{GPIOC, GPIO_MODE_IPD,    GPIO_OSPEED_50MHZ, GPIO_PIN_10, NOT_USE_ADC, "AirCondition status Pin"},
};

/**
 * @brief structure of gpio pin configuration for devices.
 * 
 */
define_GpioPin_t gpio_pin_device[SIZE_LIST_DEVICE]=
{
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4, NOT_USE_ADC,  "AirCondition control Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6, NOT_USE_ADC, "Fan Pin"},
	{GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5, NOT_USE_ADC, "LAMP Pin"},	
};

/**
 * @brief structure of status con trol of device.
 * Fisrt data of array if state on
 * Second data of array if state off
 */
define_status_device_t device_status[SIZE_LIST_DEVICE] =
{
	{RESET, SET},
	{RESET, SET},
	{RESET, SET},
};

/**
 * @brief Config for the gpio pin of sensor.
 * 
 * @param gpio_element : the position of the sensor in the sensor list.
 */
void BTS_Config_GPIO_Sensor(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_sensor[gpio_element].port, gpio_pin_sensor[gpio_element].mode, gpio_pin_sensor[gpio_element].speed, gpio_pin_sensor[gpio_element].pin);
}

/**
 * @brief Config for the gpio pin of device.
 * 
 * @param gpio_element : the position of the device in the device list.
 */
void BTS_Config_GPIO_Device(uint8_t gpio_element)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	rcu_periph_clock_enable(RCU_AF);
	gpio_pin_remap_config(GPIO_SWJ_NONJTRST_REMAP, ENABLE);
	gpio_init(gpio_pin_device[gpio_element].port, gpio_pin_device[gpio_element].mode, gpio_pin_device[gpio_element].speed, gpio_pin_device[gpio_element].pin);
}

#include "bts_device.h"

uint8_t array_data_device[DEFAULT_MAX_NUMBER_DEVICE];

/**
 * @brief Init for the all device.
 * 
 */
void BTS_Device_Init(void)
{
	BTS_Config_GPIO_Device(DEVICE_CONDITIONER);
	BTS_Config_GPIO_Device(DEVICE_FAN);
	BTS_Config_GPIO_Device(DEVICE_LAMP);
	BTS_Device_Control(DEVICE_CONDITIONER, 1);
	BTS_Device_Control(DEVICE_FAN, 1);
	BTS_Device_Control(DEVICE_LAMP, 1);
}

uint8_t BTS_Device_Get(uint8_t name_device)
{
	return 1;
}

/**
 * @brief Control the device
 * 
 * @param name_device : the position of the device in the device list.
 * @param status 
 */
void BTS_Device_Control(uint8_t name_device, uint8_t status)
{
	gpio_bit_write(gpio_pin_device[name_device].port, gpio_pin_device[name_device].pin, status);
	array_data_device[name_device] = !status;
}

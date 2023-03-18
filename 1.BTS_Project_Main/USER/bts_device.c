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
	BTS_Device_Control(DEVICE_CONDITIONER, device_status[DEVICE_CONDITIONER].off);
	BTS_Device_Control(DEVICE_FAN, device_status[DEVICE_FAN].off);
	BTS_Device_Control(DEVICE_LAMP, device_status[DEVICE_LAMP].off);
}

/**
 * @brief Control the device
 * 
 * @param name_device : the position of the device in the device list.
 * @param status 
 */
void BTS_Device_Control(uint8_t name_device, bit_status status)
{
	gpio_bit_write(gpio_pin_device[name_device].port, gpio_pin_device[name_device].pin, status);
	array_data_device[name_device] = !status;
}

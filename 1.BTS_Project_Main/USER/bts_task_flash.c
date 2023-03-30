#include "bts_task_flash.h"

uint8_t slave_id_flash;

static void SendEventSlaveID_FlashToSys(void);
static void SendQueueSlaveID_FlashToSys(void);

void BTS_RTOS_Task_Flash(void *p)
{
	SendEventSlaveID_FlashToSys();
	while(1)
	{
		vTaskDelay(TIME_DELAY_TASK_FLASH/portTICK_RATE_MS);
	}
}

static void SendEventSlaveID_FlashToSys(void)
{
	SendQueueSlaveID_FlashToSys();
	xEventGroupSetBits(EventTask2.Flash.To_Sys.EventGroup, EventTask2.Flash.To_Sys.EventBit_SlaveID);
}

static void SendQueueSlaveID_FlashToSys(void)
{
	flashInformation_t flash_infor;
	slave_id_flash = BTS_Flash_Read(ADDR_FLASH_SLAVE_ID);
	flash_infor.data[0] = slave_id_flash;
	xQueueSend(QueueTask.Flash.To_Uart.Queue_Slave_Id, (void *)&flash_infor, TIME_WAIT_QUEUE);
}

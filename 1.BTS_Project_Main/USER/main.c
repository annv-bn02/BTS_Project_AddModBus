#include "bts_sys.h"

int main()
{
	BTS_Sys_Init();
	SmartBTS_USART3_Init();
	SmartBTS_USART0_Init();
	fmc_unlock();
	fmc_page_erase(0x08008000);
	fmc_halfword_program(0x08008000, 0x0030);
	fmc_lock();
	modbus_slave_id = BTS_Flash_Read(0x08008000);
	xTaskCreate(BTS_RTOS_Task_SYS  ,(const char*) "Task System"                ,128, NULL ,1 ,NULL);
	xTaskCreate(BTS_RTOS_Task_IO   ,(const char*)  "Task GPIO"                 ,128, NULL ,1 ,NULL);
	xTaskCreate(BTS_RTOS_Task_Msg  ,(const char*) "Task Message Transmission"  ,128, NULL ,1 ,NULL);
	vTaskStartScheduler();
	return 0;
}

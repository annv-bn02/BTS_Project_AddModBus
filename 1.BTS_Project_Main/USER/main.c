#include "bts_sys.h"

int main()
{
	BTS_Sys_Init();
	SmartBTS_USART3_Init();
	SmartBTS_USART0_Init();
	if(1)
	{
		xTaskCreate(BTS_RTOS_Task_Flash ,(const char*) "Task Flash"  				,128, NULL ,1 ,NULL);
		xTaskCreate(BTS_RTOS_Task_SYS  	,(const char*) "Task System"                ,128, NULL ,1 ,NULL);
		xTaskCreate(BTS_RTOS_Task_IO   	,(const char*) "Task GPIO"                  ,128, NULL ,1 ,NULL);
		xTaskCreate(BTS_RTOS_Task_Msg  	,(const char*) "Task Message Transmission"  ,128, NULL ,1 ,NULL);
		vTaskStartScheduler();
	}
	else
	{
		NVIC_SystemReset();
	}
	return 0;
}

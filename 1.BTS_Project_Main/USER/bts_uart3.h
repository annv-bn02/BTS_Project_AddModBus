#ifndef __UART3__
#define __UART3__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"
	
#include "bts_sys.h"
	
	
extern uint8_t uart3_rxbuffer[];
extern __IO uint16_t uart3_rxcount; 
extern __IO uint8_t uart3_flag_rx;
	
void SmartBTS_USART3_Init(void);
void SmartBTS_USART3_SendChar(const uint8_t datain);
void SmartBTS_USART3_SendString(const char *datain);
void SmartBTS_USART3_SendOneByte(const uint8_t datain);
void SmartBTS_USART3_SendArrayByte(const uint8_t *datain, const uint16_t arrsize );	

uint8_t* SmartBTS_USART3_Get_Array_Data(void);
void SmartBTS_USART3_FSM_TimeOut(void);

#ifdef __cplusplus
}
#endif

#endif

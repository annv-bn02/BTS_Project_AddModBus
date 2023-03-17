#ifndef __UART__
#define __UART__
	
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include "gd32f30x.h"
#include "gd32f30x_usart.h"
	
#include "bts_sys.h"



extern uint8_t uart0_rxbuffer[];
extern __IO uint16_t uart0_rxcount; 
extern __IO uint8_t uart0_flag_rx;	
	
void SmartBTS_USART0_Init(void);
void SmartBTS_USART0_SendChar(const uint8_t datain);
void SmartBTS_USART0_SendString(const char *datain);
void SmartBTS_USART0_SendOneByte(const uint8_t datain);
void SmartBTS_USART0_SendArrayByte(const uint8_t *datain, const uint16_t arrsize );		
#ifdef __cplusplus
}
#endif

#endif

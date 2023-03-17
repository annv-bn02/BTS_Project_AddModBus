#include "bts_uart.h"


uint8_t uart0_rxbuffer[100];
__IO uint16_t uart0_rxcount; 
__IO uint8_t uart0_flag_rx = 0;
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
struct __FILE {
    int dummy;
};
FILE __stdout;

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
	SmartBTS_USART0_SendChar(ch);
	return ch;
}

/**
 * @brief Configure the UART0 for 9600 baud rate, 8 data bits, 1 stop bit, no parity
 * 
 */
void SmartBTS_USART0_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_USART0);
	rcu_periph_clock_enable(RCU_AF);
	/* configure USART Tx as alternate function push-pull */
	gpio_init(GPIOA,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
	gpio_init(GPIOA,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO_PIN_10);

	usart_baudrate_set(USART0, 9600);
	/* configure USART transmitter */
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	/* configure USART receiver */
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	/* enable USART */
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	
	/*Chon muc uu tien*/
	nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	nvic_irq_enable(USART0_IRQn, 0, 0);
	usart_enable(USART0);
}

/**
 * @brief Send a character through the USART0
 * 
 * @param datain 
 */
void SmartBTS_USART0_SendChar(const uint8_t datain)
{
	usart_data_transmit(USART0, datain);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

/**
 * @brief Send a string through the USART0
 * 
 * @param datain 
 */
void SmartBTS_USART0_SendString(const char *datain)
{
	while(*datain)
	{
		SmartBTS_USART0_SendChar((uint8_t)*datain);
		datain++;
	}
}

/**
 * @brief Send a byte through the USART0
 * 
 * @param datain 
 */
void SmartBTS_USART0_SendOneByte(const uint8_t datain)
{
	usart_data_transmit(USART0, (uint8_t)datain);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
}

/**
 * @brief Send array bytes through the USART0
 * 
 * @param datain 
 */
void SmartBTS_USART0_SendArrayByte(const uint8_t *datain, const uint16_t arrsize)
{
	uint8_t countlength;
	for(countlength = 0; countlength < arrsize; countlength++)
	{
		SmartBTS_USART0_SendOneByte(datain[countlength]);
	}
}

void USART0_IRQHandler(void)
{
	uint8_t tempchar;
	if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
	{
		tempchar = usart_data_receive(USART0);
		if(tempchar != '\n')
		{	
			uart0_rxbuffer[uart0_rxcount] = tempchar;
			uart0_rxcount++;
		}
		else
		{
			uart0_rxbuffer[uart0_rxcount] = 0x00;
			uart0_flag_rx = 1;
			uart0_rxcount = 0;
		}
	}
}


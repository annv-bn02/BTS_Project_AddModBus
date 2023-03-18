#ifndef _MODBUSRTU_SLAVE_H_
#define _MODBUSRTU_SLAVE_H_

#include "bts_sys.h"


#define SLAVEID    0x30
#define NUMBER_OF_REGISTER 40
#define NUMBER_OF_COIL 30
#define BUFFERSIZE (NUMBER_OF_REGISTER * 2 + 5)

extern uint16_t bts_modbus_register[NUMBER_OF_REGISTER];
extern uint16_t bts_modbus_coil[NUMBER_OF_COIL];

enum
{
	ReadCoil = 0x01,
	ReadHoldingRegister = 0x03,
	WriteSingleCoil = 0x05,
	WriteSingleRegister = 0x06,
	WriteMultipleCoils = 0x0F,
	WriteMultipleResisters = 0x10,
};


extern uint8_t bts_modbus_data_counter;
extern uint8_t mobus_rx_interrupt_flag;
extern uint8_t modbus_uart_time_counter;
extern uint8_t modbus_uart_complated_flag;
extern char modbus_data_receive[BUFFERSIZE];

/* Receiver functions */
void uartDataHandler(void);
void Modbus_Counter(void);
void transmitDataMake(char *msg, uint8_t Lenght);


/* Modbus Functions */
void makePacket_01(char *msg, uint8_t Lenght);
void makePacket_03(char *msg, uint8_t Lenght);
void makePacket_05(char *msg, uint8_t Lenght);
void makePacket_06(char *msg, uint8_t Lenght);
void makePacket_15(char *msg, uint8_t Lenght);
void makePacket_16(char *msg, uint8_t Lenght);


void Modbus_Send_Data(char *msg, uint8_t len);
uint8_t findByte(int16_t NumberOfCoil);
uint16_t MODBUS_CRC16(char *buf, uint8_t len );

uint16_t Control_Data_Flag(void);
#endif /* INC_MODBUSRTU_SLAVE_H_ */

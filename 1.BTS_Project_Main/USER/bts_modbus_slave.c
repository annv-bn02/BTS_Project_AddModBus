#include "bts_modbus_slave.h"

uint8_t bts_modbus_data_counter;
uint8_t mobus_rx_interrupt_flag;
uint8_t modbus_uart_time_counter;
uint8_t modbus_uart_complated_flag;
uint16_t bts_modbus_register[NUMBER_OF_REGISTER];
uint16_t bts_modbus_coil[NUMBER_OF_COIL];
char modbus_data_receive[BUFFERSIZE];
char tempmodbus_data_receive[BUFFERSIZE];
char ModbusTx[BUFFERSIZE];

uint16_t rxCRC;
uint8_t control_flag;
uint16_t control_data;
/**
 * @brief This function is flag when the master write single register to slave .
 * 
 * @return uint16_t The register value that the master wrote.
 */
uint16_t Control_Data_Flag(void)
{
	if(control_flag == 1)
	{
		control_flag = 0;
		return control_data;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief This function if choose the reponse of slave according to the function code.
 * 
 */
void transmitDataMake(char *msg, uint8_t Lenght)
{
	switch(msg[1])
	{
	case ReadCoil:
		makePacket_01(msg, Lenght);
		break;

	case ReadHoldingRegister:
		makePacket_03(msg, Lenght);
		break;

	case WriteSingleRegister:
		makePacket_06(msg, Lenght);
		break;

	case WriteSingleCoil:
		makePacket_05(msg, Lenght);
		break;

	case WriteMultipleCoils:
		makePacket_15(msg, Lenght);
		break;

	case WriteMultipleResisters:
		makePacket_16(msg, Lenght);
		break;
	}

}

/**
 * @brief This function is handle data when the master send the command done.
 * 
 */
void uartDataHandler(void)
{
	uint8_t tempCounter;
	uint16_t CRCValue;
	if(modbus_uart_complated_flag == SET)     //Data receiving is finished
	{
		modbus_uart_complated_flag = RESET;
	    memcpy(tempmodbus_data_receive, modbus_data_receive, bts_modbus_data_counter + 1);
	    tempCounter = bts_modbus_data_counter;
		bts_modbus_data_counter = 0;
		memset(modbus_data_receive, 0, BUFFERSIZE);
		memset(ModbusTx, 0, BUFFERSIZE);

		/*CRC Check*/
		CRCValue = MODBUS_CRC16(tempmodbus_data_receive, tempCounter - 2);
		rxCRC = (tempmodbus_data_receive[tempCounter -1] << 8) | (tempmodbus_data_receive[tempCounter - 2]);

		/*If check the function code if 0x06(write single registere) , set control flag and send control data*/
		if(tempmodbus_data_receive[1] == 0x06 && tempmodbus_data_receive[0] == Modbus_Slave_ID() && tempmodbus_data_receive[3] == REGISTER_ADDRESS_CONTROL_DEVICE)
		{	
			control_data = Bts_Convert_From_Bytes_To_Uint16((uint8_t)tempmodbus_data_receive[4], (uint8_t)tempmodbus_data_receive[5]);
			control_flag = 1;
		}
		else if(tempmodbus_data_receive[1] == 0x06 && tempmodbus_data_receive[0] == Modbus_Slave_ID() && tempmodbus_data_receive[3] == 86)
		{
			NVIC_SystemReset();
		}
		
		/*If the calculated CRC value and the received CRC value are equal and the Slave ID is correct, respond to the receiving data.  */
		if(rxCRC == CRCValue && tempmodbus_data_receive[0] == Modbus_Slave_ID())
		{
			transmitDataMake(&tempmodbus_data_receive[0], tempCounter);
		}

	}
}

/**
 * @brief This function is modbus counter function.
 * 
 */
void Modbus_Counter(void)
{
	if(mobus_rx_interrupt_flag == SET)
	{
		if(modbus_uart_time_counter++ > 100)
		{

			mobus_rx_interrupt_flag = RESET;
			modbus_uart_time_counter = 0;
			modbus_uart_complated_flag = SET;
		}
	}
}

/**
 * @brief This function is modbus send data function.
 * 
 */ 
void Modbus_Send_Data(char *msg, uint8_t len)
{
	SmartBTS_USART3_SendArrayByte((const uint8_t*) msg, len);
}


/*****Modbus Function*****/
//The function are used to respond to receiving modbus data.

/**
 * @brief This function is make response message of modbus function 0x01(Read multiple coils) to master by slave.
 * 
 */
void makePacket_01(char *msg, uint8_t Lenght)
{
	uint16_t RegAddress, NumberCoils, NumberByte, CRCValue;
	uint8_t tempCoil[100];
	uint8_t CoilCount, i = 0, ByteCount = 0;
	RegAddress = (msg[2] << 8) | (msg[3]);	//Starting address of the coils to be read
	NumberCoils = (msg[4] << 8) | (msg[5]); //Number of coils to be read
	NumberByte = findByte(NumberCoils);		//Data byte to be transmit

	ModbusTx[0] = msg[0];
	ModbusTx[1] = msg[1];
	ModbusTx[2] = NumberByte;

	for(CoilCount = 0; CoilCount < NumberCoils; CoilCount++)
	{
		if( CoilCount % 8 == 0 && CoilCount != 0)
		{
			ByteCount++;
			i = 0;
		}
		tempCoil[ByteCount] |= (bts_modbus_coil[RegAddress + CoilCount] << i);
		i++;
	}

	for(i = 0; i < ByteCount + 1; i++)
	{
		ModbusTx[3 + i] = tempCoil[i];
	}

	/*Calculating the CRC value of the data to be sent*/
	CRCValue = MODBUS_CRC16(ModbusTx, 3 + i);
	ModbusTx[3 + i] = (CRCValue & 0x00FF);
	ModbusTx[4 + i] = (CRCValue >> 8);
	/**************************************************/

	Modbus_Send_Data(ModbusTx, 5 + i); //Send response data
	memset(tempCoil, 0, 8 * ByteCount); //Clear tempCoil array
}

/**
 * @brief This function is make response message modbus of function 0x03(Read multiple registers) to master by slave.
 * 
 */
void makePacket_03(char *msg, uint8_t Lenght)
{
	uint8_t i, m = 0;

	uint16_t RegAddress = 0;
	uint16_t NumberOfReg = 0;
	uint16_t CRCValue;

	RegAddress = (msg[2] << 8) | (msg[3]);
	NumberOfReg = (msg[4] << 8) | (msg[5]);
	ModbusTx[0] = msg[0];
	ModbusTx[1] = msg[1];
	ModbusTx[2] = (NumberOfReg * 2);

	for(i = 0; i < NumberOfReg * 2; i += 2)
	{
		ModbusTx[3 + i] = (uint8_t)(bts_modbus_register[RegAddress + m] >> 8);
		ModbusTx[4 + i] = (uint8_t)(bts_modbus_register[RegAddress + m] & 0x00FF);
		m++;
	}

	//CRC Calculate
	CRCValue = MODBUS_CRC16(ModbusTx, 3 + (NumberOfReg * 2 ));
	ModbusTx[4 + (NumberOfReg * 2 )] = (CRCValue >> 8);
	ModbusTx[3 + (NumberOfReg * 2 )] = (CRCValue & 0x00FF);
	/********************************************************/
	Modbus_Send_Data(ModbusTx, 5 + (NumberOfReg * 2 ));
}

/**
 * @brief This function is make response message modbus of function 0x05(write single coil) to master by slave.
 * 
 */
void makePacket_05(char *msg, uint8_t Lenght)
{
	uint16_t RegAddress, RegValue;
	RegAddress = (msg[2] << 8) | (msg[3]);
	RegValue = (msg[4] << 8) | (msg[5]);

	bts_modbus_coil[RegAddress] = (bool)RegValue;

	Modbus_Send_Data(msg, Lenght);
}

/**
 * @brief This function is make response message modbus of function 0x06(write single register) to master by slave.
 * 
 */
void makePacket_06(char *msg, uint8_t Lenght)
{
	uint16_t RegAddress, RegValue;
	RegAddress = (msg[2] << 8) | (msg[3]);
	RegValue = (msg[4] << 8) | (msg[5]);
	bts_modbus_register[RegAddress] = RegValue;
	Modbus_Send_Data(msg, Lenght);
}

/**
 * @brief This function is make response message of modbus function 0x0f(write multiple coils) to master by slave.
 * 
 */
void makePacket_15(char *msg, uint8_t Lenght)
{
	uint16_t NumberOfCoils, CRCValue;
	uint8_t i,m,k;
	//uint16_t NumberOfByte, RegAddress; -> not used
	//RegAddress = (msg[2] << 8) | (msg[3]);

	NumberOfCoils = (msg[4] << 8) | (msg[5]);

	//NumberOfByte = msg[6];

	for(i = 0; i < NumberOfCoils; i++)
	{
		bts_modbus_coil[i] = (msg[7 + m] & (0x01 << k)) ;

		k++;
		if(k % 8 == 0 && k != 0)
		{
			m++;
			k = 0;
		}
	}

	memcpy(ModbusTx, msg, 6);

	CRCValue = MODBUS_CRC16(ModbusTx, 6);
	ModbusTx[6] = (CRCValue & 0x00FF);
	ModbusTx[7] = (CRCValue >> 8);
	Modbus_Send_Data(ModbusTx, 8);
}


/**
 * @brief This function is make response message of modbus function 0x10(write multiple register) to master by slave.
 * 
 */
void makePacket_16(char *msg, uint8_t Lenght)
{

	uint16_t RegAddress, NumberOfReg, CRCValue;
	uint8_t i,m = 0;
	RegAddress = (msg[2] << 8) | (msg[3]);
	NumberOfReg = (msg[4] << 8) | (msg[5]);

	for(i = 0; i < NumberOfReg; i++)
	{
		bts_modbus_register[RegAddress + i] = (uint16_t)((uint16_t)msg[7 + m] << 8) | (msg[8 + m]);
		m += 2;
	}

    memcpy(ModbusTx, msg, 6);

	CRCValue = MODBUS_CRC16(ModbusTx, 6);
	ModbusTx[6] = (CRCValue & 0x00FF);
	ModbusTx[7] = (CRCValue >> 8);
	Modbus_Send_Data(ModbusTx, 8);
}

/**
* @brief Find the number of bytes needed to store a given number of coils
* @param NumberOfCoil The number of coils to store
* @return The number of bytes needed 
*/
uint8_t findByte(int16_t NumberOfCoil)
{
	volatile uint8_t NumberOfByte = 0;

	while(NumberOfCoil >= 0)
	{
		NumberOfCoil -= 8;

		NumberOfByte++;
		if(NumberOfCoil < 0)
		{
			break;
		}
	}
	return NumberOfByte;
}

/**
* @brief Calculate the CRC-16 checksum for a Modbus message
* @param buf A pointer to the buffer containing the message
* @param len The length of the message in bytes
* @return The CRC-16 checksum as a 16-bit unsigned integer 
*/
uint16_t MODBUS_CRC16(char *buf, uint8_t len )
{
	static const uint16_t table[2] = { 0x0000, 0xA001 };
	uint16_t crc = 0xFFFF;
	unsigned int i = 0;
	char bit = 0;
	unsigned int xor = 0;

	for( i = 0; i < len; i++ )
	{
		crc ^= buf[i];

		for( bit = 0; bit < 8; bit++ )
		{
			xor = crc & 0x01;
			crc >>= 1;
			crc ^= table[xor];
		}
	}

	return crc;
}


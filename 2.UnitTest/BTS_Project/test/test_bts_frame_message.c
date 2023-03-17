#include "unity.h"
#include "bts_frame_message.h"
#include "bts_convert.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_BTS_Frame_Message_Update_Sensor(void)
{

    printf("\n\n--------------------(Start TEST bts_frame_message)--------------------\n\n");

    messageFrameMsg_t dataout;
    float data_test[DEFAULT_MAX_NUMBER_SENSOR];
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x01, 0x00, 0x2a, 0x00, 0x41, 0xa4, 0x00, 0x00, 0x41, 0xac, 0x00, 0x00, 0x41, 0xb4,
     0x00, 0x00, 0x41, 0xbc, 0x00, 0x00, 0x41, 0xc4, 0x00, 0x00, 0x41, 0xcc, 0x00, 0x00, 0x41, 0xd4, 0x00, 0x00, 0x41, 0xdc, 
     0x00, 0x00, 0x41, 0xe4, 0x00, 0x00, 0x41, 0xec, 0x00, 0x00};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Start)---------------------------------*/
    uint16_t count_arr = 0;
    for(int i = 0; i < DEFAULT_MAX_NUMBER_SENSOR; i++)
    {
        data_test[i] = 20.5 + i;
    }
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Creat_Sensor(data_test, array_out);

    for(int i = 0; i < ((DEFAULT_MAX_NUMBER_SENSOR * 4) + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }

    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

        printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_UPDATE_SENSOR);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, (DEFAULT_MAX_NUMBER_SENSOR * 4) + DEFAULT_BYTE_CHECKSUM);
    for(int i = 0; i < (DEFAULT_MAX_NUMBER_SENSOR * 4);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(dataout.Data[i], array_out[DEFAULT_BYTE + i]);
    }
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Data:        %x\n", dataout.Length);
    for(int i = 0; i < (DEFAULT_MAX_NUMBER_SENSOR * 4);i += 4)
    {

        printf("%f ", Bts_Convert_From_Bytes_To_Float(dataout.Data[i], dataout.Data[i+1], dataout.Data[i+2], dataout.Data[i+3]));
    }
    printf("\nChecksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
}

void test_BTS_Frame_Message_Update_Device(void)
{
    messageFrameMsg_t dataout;
    uint8_t data_test[DEFAULT_MAX_NUMBER_DEVICE];
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x02, 0x00, 0x2a, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
     0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 
     0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    for(int i = 0; i < DEFAULT_MAX_NUMBER_DEVICE; i++)
    {
        data_test[i] = i;
    }
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Creat_Device(data_test, array_out);

    for(int i = 0; i < (DEFAULT_MAX_NUMBER_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }

    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_UPDATE_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_MAX_NUMBER_DEVICE + DEFAULT_BYTE_CHECKSUM);
    for(int i = 0; i < DEFAULT_MAX_NUMBER_DEVICE;i++)
    {
        TEST_ASSERT_EQUAL_UINT8(dataout.Data[i], array_out[DEFAULT_BYTE + i]);
    }
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Data:        %x\n", dataout.Length);
    for(int i = 0; i < DEFAULT_MAX_NUMBER_DEVICE;i++)
    {
        printf("%d ", dataout.Data[i]);
    }
    printf("\nChecksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
}

void test_BTS_Frame_Message_Control1_Device_Lamp(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x03, 0x00};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_LAMP + 1;
    value = 0;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    
}

void test_BTS_Frame_Message_Control1_Device_Fan(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x02, 0x00};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_FAN + 1;
    value = 0;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    
}

void test_BTS_Frame_Message_Control1_Device_Conditioner(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x01, 0x00};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_CONDITIONER + 1;
    value = 0;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    
}

void test_BTS_Frame_Message_Control2_Device_Lamp(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x03, 0xff};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_LAMP + 1;
    value = 255;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    
}

void test_BTS_Frame_Message_Control2_Device_Fan(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x02, 0xff};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_FAN + 1;
    value = 255;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    
}

void test_BTS_Frame_Message_Control2_Device_Conditioner(void)
{
    messageFrameMsg_t dataout;
    uint8_t name, value;
    int16_t size_data;
    uint8_t array_out[100];
    int8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x01, 0xff};
    printf("\n--------------------(Start Create)--------------------\n");
    /*---------------------------------(Data)---------------------------------*/
    name = DEVICE_CONDITIONER + 1;
    value = 255;
    /*---------------------------------(Data)---------------------------------*/
    size_data = BTS_Frame_Control_Device(name, value, array_out);

    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE);i++)
    {
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    printf("size: %d\n",size_data);
    if(size_data > 0)
    {
        for(int i = 0; i < size_data; i++)
        {
            if(array_out[i]<= 0x0f)
            {
                printf("0%x ", array_out[i]);
            }
            else
            {
                printf("%x ", array_out[i]);
            }
        }
        printf("\n--------------------(Create Done)--------------------\n");
    }

    printf("\n--------------------(Start Detect)--------------------\n");
    size_data = DetectMessage(array_out, &dataout);
    TEST_ASSERT_EQUAL_UINT16(dataout.Start, START_BYTE);
    TEST_ASSERT_EQUAL_UINT16(dataout.TypeMessage, TYPE_MESSAGE_CONTROL_DEVICE);
    TEST_ASSERT_EQUAL_UINT16(dataout.Length, DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE_CHECKSUM);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[0], name);
    TEST_ASSERT_EQUAL_UINT8(dataout.Data[1], value);
    TEST_ASSERT_EQUAL_UINT16(dataout.Crc, Bts_Convert_From_Bytes_To_Uint16(array_out[size_data - 2], array_out[size_data - 1]));
    printf("StartFrame:  %x\n", dataout.Start);
    printf("TypeMessage: %x\n", dataout.TypeMessage);
    printf("Length:      %x\n", dataout.Length);
    printf("Name:        %x\n", dataout.Data[0]);
    printf("Value:       %x\n", dataout.Data[1]);
    printf("Checksum:    %x\n", dataout.Crc);
    printf("\n--------------------(Detect Done)--------------------\n");
    

    printf("\n\n--------------------(End TEST bts_frame_message)--------------------\n\n");

}

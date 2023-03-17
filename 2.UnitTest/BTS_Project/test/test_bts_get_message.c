
#include "unity.h"

#include "bts_get_message.h"
#include "bts_convert.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_BTS_Get_Message_Control1_Device_Lamp(void)
{

    printf("\n\n--------------------(Start TEST bts_get_message)--------------------\n\n");

    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x03, 0x00, 0x8e, 0xf1};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");
    
}

void test_BTS_Get_Message_Control1_Device_Fan(void)
{
    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x02, 0x00, 0x8f, 0x61};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");
    
}

void test_BTS_Get_Message_Control1_Device_Conditioner(void)
{
    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x01, 0x00, 0x8f, 0x91};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");
}

void test_BTS_Get_Message_Control2_Device_Lamp(void)
{
    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x03, 0xff, 0xce, 0xb1};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");
    
}

void test_BTS_Get_Message_Control2_Device_Fan(void)
{
    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x02, 0xff, 0xcf, 0x21};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");
    
}

void test_BTS_Get_Message_Control2_Device_Conditioner(void)
{
    uint8_t array_out[100];
    uint8_t array_test[100] = {0x55, 0xaa, 0x03, 0x00, 0x04, 0x00, 0x01, 0xff, 0xcf, 0xd1};
    printf("\n--------------------(Start Get)--------------------\n");
    /*---------------------------------(Data)-------------------------------*/
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        BTS_Get_Message(array_test[i], array_out);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM);i++)
    {
    
        TEST_ASSERT_EQUAL_UINT8(array_test[i], array_out[i]);
    }
    for(int i = 0; i < (DEFAULT_BYTE_CONTROL_DEVICE + DEFAULT_BYTE + DEFAULT_BYTE_CHECKSUM); i++)
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
    printf("\n--------------------(Get Done)--------------------\n");

    printf("\n\n--------------------(Start END bts_get_message)--------------------\n\n");

}

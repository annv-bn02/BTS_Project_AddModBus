#include "unity.h"

#include "bts_convert.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_BTS_Convert_Float_To_Bytes(void)
{

    printf("\n\n--------------------(Start TEST bts_convert)--------------------\n\n");

    float data_in = 1.67;
    uint8_t data_test[4] = {0x8f, 0xc2, 0xd5, 0x3f};
    printf("\n-----------Convert Float To Bytes--------\n");
    uint8_t *data_out = Bts_Convert_From_Float_To_Bytes(data_in);
    for(int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(data_test[i], data_out[i]);
    }
    printf("Data convert: ");
    for(int i = 0; i < 4; i++)
    {
        printf("%x ", data_out[i]);
    }
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Int_To_Bytes(void)
{
    int data_in = 30202023;
    uint8_t data_test[4] = {0xa7, 0xd8, 0xcc, 0x01};
    printf("\n-----------Convert Int To Bytes--------\n");
    uint8_t *data_out = Bts_Convert_From_Int_To_Bytes(data_in);
    for(int i = 0; i < 4; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(data_test[i], data_out[i]);
    }
    printf("Data convert: ");
    for(int i = 0; i < 4; i++)
    {
        printf("%x ", data_out[i]);
    }
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Uint16_To_Bytes(void)
{
    uint16_t data_in = 578;
    uint8_t data_test[2] = {0x42, 0x02};
    printf("\n-----------Convert Float To Bytes--------\n");
    uint8_t *data_out = Bts_Convert_From_Uint16_To_Bytes(data_in);
    for(int i = 0; i < 2; i++)
    {
        TEST_ASSERT_EQUAL_UINT8(data_test[i], data_out[i]);
    }
    printf("Data convert: ");
    for(int i = 0; i < 2; i++)
    {
        printf("%x ", data_out[i]);
    }
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Float_To_Uint16(void)
{
    float data_in = 121233.5;
    uint16_t data_test[2] = {0xc8c0, 0x47ec};
    printf("\n-----------Convert Float To Bytes--------\n");
    uint16_t *data_out = Bts_Convert_From_Float_To_Uint16(data_in);
    for(int i = 0; i < 2; i++)
    {
        printf("%x ", data_out[i]);
    }
    printf("\n----------------Convert Done--------------\n");
    for(int i = 0; i < 2; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(data_test[i], data_out[i]);
    }
    printf("Data convert: ");

}

void test_BTS_Convert_Uint16_To_Float(void)
{
    float data_test = 121233.5;
    uint16_t data_in[2] = {0xc8c0, 0x47ec};
    printf("\n-----------Convert Bytes To Float--------\n");
    float data_out = Bts_Convert_From_Uint16_To_Float(data_in[0], data_in[1]);
    TEST_ASSERT_EQUAL_FLOAT(data_test, data_out);
    printf("Data convert: %f ", data_out);
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Bytes_To_Float(void)
{
    float data_test = 1.67;
    uint8_t data_in[4] = {0x3f, 0xd5, 0xc2, 0x8f};
    printf("\n-----------Convert Bytes To Float--------\n");
    float data_out = Bts_Convert_From_Bytes_To_Float(data_in[0], data_in[1], data_in[2], data_in[3]);
    TEST_ASSERT_EQUAL_FLOAT(data_test, data_out);
    printf("Data convert: %f ", data_out);
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Bytes_To_Int(void)
{
    int data_test = 30202023;
    uint8_t data_in[4] = {0x01, 0xcc, 0xd8, 0xa7};
    printf("\n-----------Convert Bytes To Int--------\n");
    int data_out = Bts_Convert_From_Bytes_To_Int(data_in[0], data_in[1], data_in[2], data_in[3]);
    TEST_ASSERT_EQUAL_INT(data_test, data_out);
    printf("Data convert: %d ", data_out);
    printf("\n----------------Convert Done--------------\n");
}

void test_BTS_Convert_Bytes_To_Uint16(void)
{
    uint16_t data_test = 578;
    uint8_t data_in[2] = {0x42, 0x02};
    printf("\n-----------Convert Bytes To Uint16--------\n");
    uint16_t data_out = Bts_Convert_From_Bytes_To_Uint16(data_in[0], data_in[1]);
    TEST_ASSERT_EQUAL_FLOAT(data_test, data_out);
    printf("Data convert: %d ", data_out);
    printf("\n----------------Convert Done--------------\n");

    printf("\n\n--------------------(End TEST bts_convert)--------------------\n\n");

}

#include "src/bts_convert.h"
#include "src/bts_get_message.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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



    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        BTS_Get_Message(array_test[i], array_out);

    }

    for(int i = 0; i < (2 + 6 + 2);i++)

    {



        UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((array_test[i])), (UNITY_INT)(UNITY_UINT8 )((array_out[i])), (

       ((void *)0)

       ), (UNITY_UINT)(185), UNITY_DISPLAY_STYLE_UINT8);

    }

    for(int i = 0; i < (2 + 6 + 2); i++)

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

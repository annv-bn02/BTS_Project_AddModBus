/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_BTS_Convert_Float_To_Bytes(void);
extern void test_BTS_Convert_Int_To_Bytes(void);
extern void test_BTS_Convert_Uint16_To_Bytes(void);
extern void test_BTS_Convert_Bytes_To_Float(void);
extern void test_BTS_Convert_Bytes_To_Int(void);
extern void test_BTS_Convert_Bytes_To_Uint16(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_bts_convert.c");
  run_test(test_BTS_Convert_Float_To_Bytes, "test_BTS_Convert_Float_To_Bytes", 13);
  run_test(test_BTS_Convert_Int_To_Bytes, "test_BTS_Convert_Int_To_Bytes", 34);
  run_test(test_BTS_Convert_Uint16_To_Bytes, "test_BTS_Convert_Uint16_To_Bytes", 52);
  run_test(test_BTS_Convert_Bytes_To_Float, "test_BTS_Convert_Bytes_To_Float", 70);
  run_test(test_BTS_Convert_Bytes_To_Int, "test_BTS_Convert_Bytes_To_Int", 81);
  run_test(test_BTS_Convert_Bytes_To_Uint16, "test_BTS_Convert_Bytes_To_Uint16", 92);

  return UnityEnd();
}
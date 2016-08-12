#include "unity.h"
#include "DIVW.h"
#include "MCU_Operation.h"
#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include <malloc.h>
#include "ErrorObject.h"
#include "CException.h"

void setUp(void)
{
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
}

void tearDown(void)
{
  free(cpu);
}

/**
*   X = 0X3333;
*   Y = 0X1111;
*   
*   quotient = 0X3333 /0X1111 = 0x03
*   remainder = 0X3333 /0x11 = 0;
*
*  X = quotient
*  A = remainder
*/
void test_divw_x_y(void)
{
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X11;
  YL = 0X11;
  
  
  uint8_t instr[] = {0XAB};
    
  int length = divw_x_y(instr);
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x03, XL);
  TEST_ASSERT_EQUAL_INT8(0x00, YH);
  TEST_ASSERT_EQUAL_INT8(0x00, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

/**
*   X = 0X3333;
*   Y = 0X2222;
*   
*   quotient = 0X3333 /0X1111 = 0x01
*   remainder = 0X3333 /0x2222 = 0x1111;
*
*  X = quotient
*  A = remainder
*/
void test_divw_x_y_with_remaidner(void)
{
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X22;
  YL = 0X22;
  
  uint8_t instr[] = {0XAB};
    
  int length = divw_x_y(instr);
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x01, XL);
  TEST_ASSERT_EQUAL_INT8(0x11, YH);
  TEST_ASSERT_EQUAL_INT8(0x11, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

void test_divw_x_y_with_x_equal_0(void)
{
  XH = 0X00;
  XL = 0X00;
  
  YH = 0X22;
  YL = 0X22;
  
  uint8_t instr[] = {0XAB};
    
  int length = divw_x_y(instr);
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x00, XL);
  TEST_ASSERT_EQUAL_INT8(0x00, YH);
  TEST_ASSERT_EQUAL_INT8(0x00, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}

void test_divw_x_y_with_y_equal_0_should_set_C_and_get_error(void)
{
  CEXCEPTION_T err;
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X00;
  YL = 0X00;
  
  uint8_t instr[] = {0XAB};
  
  Try{
    int length = divw_x_y(instr);
    TEST_FAIL_MESSAGE("Expected ERR_DIVIDER_IS_0");
    
  TEST_ASSERT_EQUAL(1, length);

    
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_DIVIDER_IS_0, err, "Expected ERR_DIVIDER_IS_0");
  }
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);
}


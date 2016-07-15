#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>
#include "DIV.h"
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

/** quotient = 0x3322 /0x11 = 0x0302
*   remainder =  0x3322 /0x11 = 0;
*
*  X = quotient
*  A = remainder
*/
void test_mcu_div_with_normal_division(void)
{
  XH = 0X33;
  XL = 0X22;
  
  A = 0X11;
    
  mcu_div( &XH);
  TEST_ASSERT_EQUAL_INT16(0x03, XH);
  TEST_ASSERT_EQUAL_INT16(0x02, XL);
  TEST_ASSERT_EQUAL_INT8(0x00, A);
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

/** quotient = 0x3322 /0x33 = 0x0100
*   remainder =  0x3322 /0x33 = 0x22;
*
*  X = quotient
*  A = remainder
*/
void test_mcu_div_with_remainder_22(void)
{
  XH = 0X33;
  XL = 0X22;
  
  A = 0X33;
    
  mcu_div( &XH);
  TEST_ASSERT_EQUAL_INT16(0x01, XH);
  TEST_ASSERT_EQUAL_INT16(0x00, XL);
  TEST_ASSERT_EQUAL_INT8(0x22, A);
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


void test_mcu_div_with_dividend_0_and_set_Z_to_1(void)
{
  XH = 0X00;
  XL = 0X00;
  
  A = 0X33;
    
  mcu_div( &XH);

  TEST_ASSERT_EQUAL_INT8(0x0, A);
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}

void test_mcu_div_with_divider_0_should_set_c_and_get_error(void)
{
  CEXCEPTION_T err;
  XH = 0X33;
  XL = 0X33;
  
  A = 0X00;

  Try{
    
  mcu_div( &XH);
  TEST_FAIL_MESSAGE("Expected ERR_DIVIDER_IS_0");
    

  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_DIVIDER_IS_0, err, "Expected ERR_DIVIDER_IS_0");
  }
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);
    
}
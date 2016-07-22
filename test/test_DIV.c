#include "unity.h"
#include "DIV.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>



void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
   free(cpu);
}

/** quotient = 0x3322 /0x33 = 0x0100
*   remainder  0x3322 /0x33 = 0x22;
*
*  X = quotient
*  A = remainder
*/
void test_div_x_a(void)
{
  XH = 0X33;
  XL = 0X22;
  
  A = 0X33;
  uint8_t instr[] = {0XAB};
    
  int length = div_x_a(instr);
  TEST_ASSERT_EQUAL_INT16(0x01, XH);
  TEST_ASSERT_EQUAL_INT16(0x00, XL);
  TEST_ASSERT_EQUAL_INT8(0x22, A);
  TEST_ASSERT_EQUAL(1, length);
}

void test_div_y_a(void)
{
  YH = 0X33;
  YL = 0X22;
  
  A = 0X33;
  uint8_t instr[] = {0XAB};
    
  int length = div_y_a(instr);
  TEST_ASSERT_EQUAL_INT16(0x01, YH);
  TEST_ASSERT_EQUAL_INT16(0x00, YL);
  TEST_ASSERT_EQUAL_INT8(0x22, A);
  TEST_ASSERT_EQUAL(2, length);
}

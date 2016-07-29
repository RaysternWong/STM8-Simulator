#include "unity.h"
#include "NEGW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  clearConditionCodeRegister(&(cpu->ccr));  
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/*

  NEGW X X ← 0000 - X

*/

void test_negw_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, negw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0xEFD5, X);  // 0 - 0x102b = 0xEFD5
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result != 0
}

void test_negw_x_set_V_flag(void){
  SET_X(0X8000);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, negw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0X8000, X);  // 0 - 0X8000 = 0X8000
  
  TEST_ASSERT_EQUAL(1, V); // content of "dst" was $8000
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result != 0
}

void test_negw_x_set_Z_flag(void){
  SET_X(0x0);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, negw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0, X);  // 0 - 0 = 0
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

void test_negw_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(2, negw_y(instr));
  TEST_ASSERT_EQUAL_INT8( 0xEFD5, Y); // 0 - 0x102b = 0xEFD5
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result > 0
}

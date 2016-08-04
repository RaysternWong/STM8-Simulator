#include "unity.h"
#include "CLRW.h"
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
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}


void test_clrw_x(void){
  SET_X(0x1111);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, clrw_x(instr));
  TEST_ASSERT_EQUAL_INT8(0, X);
  TEST_ASSERT_EQUAL_INT8(0, N);
  TEST_ASSERT_EQUAL_INT8(1, Z);
}

void test_clrw_y(void){
  SET_Y(0x1111);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(2, clrw_y(instr));
  TEST_ASSERT_EQUAL_INT8(0, X);
  TEST_ASSERT_EQUAL_INT8(0, N);
  TEST_ASSERT_EQUAL_INT8(1, Z);
}
#include "unity.h"
#include "INCW.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>
#include "ErrorObject.h"
#include "Description.h"


void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_incw_x(void){

  SET_X(0x2222);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, incw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x2223, X);
}

void test_incw_x_set_V_flag(void){

  SET_X(0x2222);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, incw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x2223, X);
}

void test_incw_y(void){

  SET_Y(0x2222);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(2, incw_y(instr));
  TEST_ASSERT_EQUAL_INT16(0x2223, Y);
}
#include "unity.h"
#include "DECW.h"
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

void test_decw_x(void){

  SET_X(0x2222);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, decw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x2221, X);
}

void test_decw_x_set_V_flag(void){

  SET_X(0x8000);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, decw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x7FFF, X);
  TEST_ASSERT_EQUAL_INT8(1, V); // 0x8000(-ve) - 1(+ve) = 0x7fff(-ve)
}

void test_decw_y(void){

  SET_Y(0x2222);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(2, decw_y(instr));
  TEST_ASSERT_EQUAL_INT16(0x2221, Y);
}
#include "unity.h"
#include "EXGW.h"
#include "EXG.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>


void setUp(void){
  instantiateCPU();
}

void tearDown(void){
  free(cpu);
}

void test_exgw_x_y(void){
  SET_X(0X2222);
  SET_Y(0X5555);

  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, exgw_x_y(instr));
  TEST_ASSERT_EQUAL_INT8(0X5555, X);
  TEST_ASSERT_EQUAL_INT8(0X2222, Y);
}



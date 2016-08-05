#include "unity.h"
#include "CCF.h"
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

void test_ccf_complement_to_1(void){
  C = 0;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, ccf(instr));
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_ccf_complement_to_0(void){
  C = 1;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, ccf(instr));
  TEST_ASSERT_EQUAL_INT8(0, C);
}
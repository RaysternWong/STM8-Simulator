#include "unity.h"
#include "RVF.h"
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

void test_rvf(void){

  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, rvf(instr));
  TEST_ASSERT_EQUAL_INT8(0, V);
}
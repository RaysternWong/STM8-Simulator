#include "unity.h"
#include "SIM.h"
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

void test_sim(void){

  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, sim(instr));
  TEST_ASSERT_EQUAL_INT8(1, L0);
  TEST_ASSERT_EQUAL_INT8(1, L1);
}
#include "unity.h"
#include "SWAPW.h"
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

void test_swapw_x(void)
{
  SET_X(0xBBCC);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, swapw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0xCCBB, X); 
  TEST_ASSERT_EQUAL_INT8(1, N); //bit 15 is 1
  TEST_ASSERT_EQUAL_INT8(0, Z); 
}

void test_swapw_y(void)
{
  SET_Y(0x0000);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(2, swapw_y(instr));
  TEST_ASSERT_EQUAL_INT16(0x0, Y); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(1, Z); 
}
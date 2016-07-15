#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>
#include "Memory.h"
#include "ErrorObject.h"

void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
  free(cpu);
}

/**
*     uint16_t getBigEndianWord(uint8_t mostByte, uint8_t leastByte)
*
*/ 

void test_getBigEndianWord(void){
  
  uint8_t instr[] = {0XAB, 0xCC};
  uint16_t fullByte = getBigEndianWord(instr);
  
  TEST_ASSERT_EQUAL_INT16(0xABCC, fullByte);
}

// #define X   getBigEndianWord(&XH) in mcu_operation.h
void test_getBigEndianWord_given_set_XH_and_XL_then_get_back_X(void){
  XH = 0X33;
  XL = 0X77;
  TEST_ASSERT_EQUAL_INT16(0x3377, X);
}


// #define Y   getBigEndianWord(&YH) in mcu_operation.h
void test_getBigEndianWord_given_set_YH_and_YL_then_get_back_Y(void){
  
  YH = 0X33;
  YL = 0X77;
  TEST_ASSERT_EQUAL_INT16(0x3377, Y);
}


// #define SP  getBigEndianWord(&SPH) in mcu_operation.h
void test_getBigEndianWord_given_set_SPH_and_SPL_then_get_back_SP(void){
  
  SPH = 0X33;
  SPL = 0X77;
  TEST_ASSERT_EQUAL_INT16(0x3377, SP);
}

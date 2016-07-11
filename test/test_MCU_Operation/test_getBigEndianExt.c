#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


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

void test_getBigEndianExt(void){
  
  uint8_t instr[] = {0XAB, 0xCC, 0XDD};
  uint32_t fullByte = getBigEndianExt(instr);
  
  TEST_ASSERT_EQUAL_INT16(0xABCCDD, fullByte);
}

//#define PC       getBigEndianExt(&PCE) in mcu_operation.h
void test_getBigEndianWord_given_PC_marco(void){
  PCE = 0XAA;
  PCH = 0XDD;
  PCL = 0XFF;

  TEST_ASSERT_EQUAL_INT32(0xAADDFF, PC);
}




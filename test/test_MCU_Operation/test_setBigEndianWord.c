#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


void setUp(void)
{

}

void tearDown(void)
{

}

void test_initMostLeastByte_given_fullByte_is_0x22cd(void){
  
  uint16_t fullByte = 0x22cd;
  
  uint8_t mostByte , leastByte;
  
  initMostLeastByte(&mostByte, &leastByte, fullByte);
  
  TEST_ASSERT_EQUAL_INT8(0x22, mostByte);
  TEST_ASSERT_EQUAL_INT8(0xcd, leastByte);
}

// -0x22cd = 0xdd33
void test_initMostLeastByte_given_fullByte_is_nrg_0x22cd(void){
  
  uint16_t fullByte = -0x22cd;
  
  
  uint8_t mostByte , leastByte;

  initMostLeastByte(&mostByte, &leastByte, fullByte);
  
  TEST_ASSERT_EQUAL_INT8(0xdd, mostByte);
  TEST_ASSERT_EQUAL_INT8(0x33, leastByte);
}
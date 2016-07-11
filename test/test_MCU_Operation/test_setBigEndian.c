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

void test_setBigEndianWord_given_word_is_0x22cd(void){
  
  uint16_t word = 0x22cd;
  
  uint8_t mostByte , leastByte;
  
  setBigEndianWord(&mostByte, &leastByte, word);
  
  TEST_ASSERT_EQUAL_INT8(0x22, mostByte);
  TEST_ASSERT_EQUAL_INT8(0xcd, leastByte);
}

// -0x22cd = 0xdd33
void test_setBigEndianWord_given_word_is_nrg_0x22cd(void){
  
  uint16_t word = -0x22cd;
  
  
  uint8_t mostByte , leastByte;

  setBigEndianWord(&mostByte, &leastByte, word);
  
  TEST_ASSERT_EQUAL_INT8(0xdd, mostByte);
  TEST_ASSERT_EQUAL_INT8(0x33, leastByte);
}

void test_setBigEndianExt(void){
  
  uint32_t ext = 0x117788;
  
  
  uint8_t extByte, msbByte , lsbByte;

  setBigEndianExt(&extByte, &msbByte, &lsbByte, ext);
  
  TEST_ASSERT_EQUAL_INT8(0x11, extByte);
  TEST_ASSERT_EQUAL_INT8(0x77, msbByte);
  TEST_ASSERT_EQUAL_INT8(0x88, lsbByte);
}
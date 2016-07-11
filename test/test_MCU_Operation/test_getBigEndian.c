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

/**
*     uint16_t getBigEndianWord(uint8_t mostByte, uint8_t leastByte)
*
*/ 

void test_getBigEndianWord_given_mostByte_is_0x24_leastByte_is_0x31_should_return_0x2341(void){
  
  uint8_t mostByte  = 0x24;
  uint8_t leastByte = 0x31;
  
  uint16_t fullByte = getBigEndianWord(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0x2431, fullByte);
}

// -0x7f = 0x81
void test_getBigEndianWord_given_mostByte_is_neg_0x7f_leastByte_is_0xab_should_return_0x81ab(void){
  
  uint8_t mostByte  = -0x7f;
  uint8_t leastByte = 0xab;
  
  uint16_t fullByte = getBigEndianWord(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0x81ab, fullByte);
}


 // -0x34 = 0xcc , -0x21 = 0xdf
void test_getBigEndianWord_given_mostByte_is_neg_0x34_leastByte_is_neg_0x21_should_return_0xccdf(void){
  
  uint8_t mostByte  = -0x34;
  uint8_t leastByte = -0x21;
  
  uint16_t fullByte = getBigEndianWord(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0xccdf, fullByte);
}

void test_getBigEndianExt_given_0xABCDEF(void)
{
  uint32_t extend =  getBigEndianExt(0xab, 0xcd, 0xef);
  TEST_ASSERT_EQUAL_INT32(0xabcdef, extend);
  
}

void test_getBigEndianExt_given_0x0(void)
{
  uint32_t extend =  getBigEndianExt(0x0, 0x0, 0x0);
  TEST_ASSERT_EQUAL_INT32(0x0, extend);
  
}

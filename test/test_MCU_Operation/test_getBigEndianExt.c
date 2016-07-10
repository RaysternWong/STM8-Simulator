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
*     uint16_t combineMostLeastByte(uint8_t mostByte, uint8_t leastByte)
*
*/ 

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
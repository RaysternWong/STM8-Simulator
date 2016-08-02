#include "unity.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "CPUConfig.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include "MCU_Operation.h"
#include "Description.h"

void setUp(void)
{ // RAM_SIZE   FULL_SIZE
  ramBlock = createMemoryBlock(RAM_START_ADDR, RAM_SIZE);
  setMemoryTable( ramMemory , 0 , RAM_SIZE );
}

void tearDown(void)
{
  free(ramBlock);
}

void test_MEM_WRITE_BYTE_and_MEM_READ_BYTE(void)
{
  uint32_t addr = 0x0FF;

  MEM_WRITE_BYTE(addr,0xBB);
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr));
  
  TEST_ASSERT_EQUAL_INT8(0xBB, MEM_READ_BYTE(addr));
}


void test_MEM_WRITE_WORD_and_MEM_READ_WORD(void)
{
  uint32_t addr  = 0x01FF;
  MEM_WRITE_WORD(addr ,0xAABB);
 
  TEST_ASSERT_EQUAL_INT8(0xAA, RAM_ARR(addr));
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr+1));
  
  TEST_ASSERT_EQUAL_INT16(0xAABB, MEM_READ_WORD(addr));
}

void test_MEM_WRITE_EXT_and_MEM_READ_EXT(void)
{
  uint32_t addr  = 0x01FF;

  MEM_WRITE_EXT(addr ,0x22AABB);
  TEST_ASSERT_EQUAL_INT8(0x22, RAM_ARR(addr));
  TEST_ASSERT_EQUAL_INT8(0xAA, RAM_ARR(addr+1));
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr+2));
  
  TEST_ASSERT_EQUAL_INT32(0x22AABB, MEM_READ_EXT(addr));
}
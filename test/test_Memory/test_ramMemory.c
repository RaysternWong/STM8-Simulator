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

void test_ramMemory_write_in_0xBB_and_getBack_0xBB(void)
{
  uint8_t data = 0xBB;
  
  uint32_t addr = 0x0FF;
  uint8_t size = 0x1;
  
  MEM_WRITE_BYTE(addr,data);
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr));
  
  uint8_t value = MEM_READ_BYTE(addr);
  TEST_ASSERT_EQUAL_INT8(0xBB, value);
}

void test_ramMemory_write_in_0xBBCC_and_getBack_0xBBCC(void)
{
  uint16_t data = 0xBBCC;
  
  uint32_t addr = 0x03FF;

  uint8_t size = 0x1;
  
  MEM_WRITE_BYTE(addr,data);
  TEST_ASSERT_EQUAL_INT8(0xBBCC, RAM_ARR(addr));

  uint8_t value = MEM_READ_BYTE(addr);
  TEST_ASSERT_EQUAL_INT8(0xBBCC, value);
}

void test_ramMemory_write_in_AA_BB_then_MEM_READ_WORD_should_get_0xAABB(void)
{
  uint8_t msb = 0xAA;
  uint8_t lsb = 0xBB;

  uint32_t addr  = 0x01FF;
  uint32_t addr1 = addr+1;

  
  MEM_WRITE_BYTE(addr ,msb);
  MEM_WRITE_BYTE(addr1 ,lsb);
  TEST_ASSERT_EQUAL_INT8(0xAA, RAM_ARR(addr));
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr1));
  
  uint16_t word = MEM_READ_WORD(addr);
  TEST_ASSERT_EQUAL_INT16(0xAABB, word);
}

void test_ramMemory_write_in_AA_BB_then_MEM_READ_EXT_should_get_0xAABB(void)
{
  uint8_t extb = 0x22;
  uint8_t msb = 0xAA;
  uint8_t lsb = 0xBB;

  uint32_t addr  = 0x01FF;
  uint32_t addr1 = addr+1;
  uint32_t addr2 = addr+2;

  
  MEM_WRITE_BYTE(addr  ,extb);
  MEM_WRITE_BYTE(addr1 ,msb);
  MEM_WRITE_BYTE(addr2 ,lsb);
  TEST_ASSERT_EQUAL_INT8(0x22, RAM_ARR(addr));
  TEST_ASSERT_EQUAL_INT8(0xAA, RAM_ARR(addr1));
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr2));
  
  uint32_t ext = MEM_READ_EXT(addr);
  TEST_ASSERT_EQUAL_INT32(0x22AABB, ext);
}
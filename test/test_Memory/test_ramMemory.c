#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

#define MEM_READ_BYTE(addr)  memoryTable[addr/0x100](MEM_READ, addr, 1)
#define MEM_READ_WORD(addr)  memoryTable[addr/0x100](MEM_READ, addr, 2)
#define MEM_WRITE_BYTE(addr,data)  memoryTable[addr/0x100](MEM_WRITE, addr, data)

void setUp(void)
{
  ramBlock = createMemoryBlock(RAM_START_ADDR, RAM_SIZE);
  setMemoryTable( ramMemory , 0 , 0x3FF );
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




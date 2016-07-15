#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include "MCU_Operation.h"
#include "Description.h"
#include "CException.h"

void setUp(void)
{ 

// RAM_SIZE   FULL_SIZE
  // ramBlock = createMemoryBlock(RAM_START_ADDR, RAM_SIZE);
  // setMemoryTable( ramMemory , 0 , RAM_SIZE );
}

void tearDown(void)
{
  //free(ramBlock);
}

void test_noMemory(void)
{
  uint8_t data = 0xBB;
  
  uint32_t addr = 0x0FF;
  uint8_t size = 0x1;
  
  MEM_WRITE_BYTE(addr,data);
  TEST_ASSERT_EQUAL_INT8(0xBB, RAM_ARR(addr));
  
  uint8_t value = MEM_READ_BYTE(addr);
  TEST_ASSERT_EQUAL_INT8(0xBB, value);
}


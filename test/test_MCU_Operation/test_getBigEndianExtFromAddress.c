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
  ramBlock = createMemoryBlock(RAM_START_ADDR, 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF );
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}


void test_getBigEndianExtFromAddress(void){
  
  uint32_t addr = 0x11bb;
  uint32_t addr1= addr + 1;
  uint32_t addr2= addr + 2;

  MEM_WRITE_BYTE(addr  ,0x71);
  MEM_WRITE_BYTE(addr1 ,0X88);
  MEM_WRITE_BYTE(addr2 ,0X99);
  
  uint32_t ext = getBigEndianExtFromAddress(addr);
  TEST_ASSERT_EQUAL_INT32(0X718899, ext);
}



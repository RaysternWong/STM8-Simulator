#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"
#include <stdint.h>
#include <stdio.h>


#define MEM_READ_BYTE(addr)  memoryTable[addr/0x100](MEM_READ, addr, 1)
#define MEM_READ_WORD(addr)  memoryTable[addr/0x100](MEM_READ, addr, 2)


void setUp(void)
{
}

void tearDown(void)
{
}

void test_ram_Memory_write_in_0xBB_and_getBack_0xBB(void)
{
  uint8_t data = 0xBB;
  
  uint8_t addr = 2;
  uint8_t size = 1;
  
  
  //int value = memoryTable[0X00](MEM_READ, addr, 1) ;
  uint8_t value = memoryTable[0X03]( MEM_READ, size) ;
  
 
  TEST_ASSERT_EQUAL_INT8(0x01, value);
}




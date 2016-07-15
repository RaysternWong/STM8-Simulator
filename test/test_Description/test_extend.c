#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to 27FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0x17FFFF);
  setMemoryTable( ramMemory , 0 , 0x17FFFF); 

}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

// return the address of longPtrE
void test_GET_EXT_MEM(void){
  uint8_t instr[] = { 0xAB, 0x11,0x22,0x33};
  uint8_t *opcode = instr;
  
  TEST_ASSERT_EQUAL_INT32(0X112233, GET_EXT_MEM(opcode) );
}
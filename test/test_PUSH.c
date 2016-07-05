#include "unity.h"
#include "PUSH.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  
  ramBlock = createMemoryBlock(RAM_START_ADDR, 0xFFFF);
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  SET_SP(0x1290);
  
 // MEM_WRITE_BYTE( SP ,  0x09);
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}

// This function is in mcu_operation.c, because is has use of sharing 
void test_mcu_push(void)
{
	TEST_IGNORE_MESSAGE("Implement me!");
}

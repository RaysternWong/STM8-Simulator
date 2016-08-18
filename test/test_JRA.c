#include "unity.h"
#include "JRA.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  pcToLoad = malloc(sizeof(uint32_t));
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
  free(pcToLoad);
}

void test_jra_shortoff(void)
{
	SET_PC(0X7777);
  uint8_t instr[] = { 0xAB, 0x55};
  
  TEST_ASSERT_EQUAL_INT8( 2, jra_shortoff(instr) );  
  TEST_ASSERT_EQUAL_INT32( 0X7777 + 0x55 + 2 , *pcToLoad ); 
}


#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include "MCU_Operation.h"
#include "Description.h"
#include "CException.h"
#include "ErrorObject.h"


void setUp(void)
{                          
  setMemoryTable( noMemory , STM8_START_ADDR , STM8_END_ADDR ); //Assign noMemory to each row of memoryTable
}

void tearDown(void)
{
  
}


void test_setMemoryTable_given_set_ramMemory_from_startAddr_0x0_and_memSize_0x25(void){
  uint32_t startAddr = 0;
  uint8_t memSize = 0x25;
  
  setMemoryTable( ramMemory , startAddr , memSize );
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0]);
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[1]);  //0x25/100 is < 1 , 
}

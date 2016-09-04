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

}

void tearDown(void)
{
  
}

/**
*     Ram address range
*
*     0x00 0000  ----------->  0x00 03FF
*
*
*
*/


void test_assignNoMemoryToWholeMemoryTable(void){
  assignNoMemoryToWholeMemoryTable() ;
  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x0]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x2]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x7]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x9]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0xA]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x49]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x49]);  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x27F]);  

}

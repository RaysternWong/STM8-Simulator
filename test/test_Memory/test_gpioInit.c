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
  assignNoMemoryToWholeMemoryTable(); // 0x00 to 0x027FFF
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


void test_gpioInit_should_set_the_gpio_memory_accordingly(void){
  gpioInit  (GPIO_START_ADDR  , GPIO_SIZE  ); 
  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x4F]);  // test is the corner memory space is noMemory
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x50]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x51]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x52]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x53]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x54]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x55]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x56]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x57]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x58]);  // test is the corner memory space is noMemory
}

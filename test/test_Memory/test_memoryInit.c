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

/*
                              // 0x00          0x027FFF
  setMemoryTable(noMemory, STM8_START_ADDR, STM8_END_ADDR );
  ramInit   (RAM_START_ADDR   , RAM_SIZE   ); //0x0 ---> 0x03FF
  gpioInit  (GPIO_START_ADDR  , GPIO_SIZE  ); //0x5000----> 0x57FF
  eepromInit(EEPROM_START_ADDR, EEPROM_SIZE); //0x4000----> 0x427F
  cpuInit   (CPU_START_ADDR, CPU_SIZE);  //0x7F00 - 0x7FFF
  flashInit (OPTION_BYTE_START_ADDR, GPIO_START_ADDR - 1- OPTION_BYTE_START_ADDR); //0x4800 --> 0x4FFF

*/

void test_memoryInit_should_set_the_memory_function_accordingly_to_the_address(void){
  

  memoryInit();
  
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x0]); 
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x1]); 
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x2]); 
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x3]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x4]);  // test is the corner memory space is noMemory
  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x47]);  // test is the corner memory space is noMemory
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x48]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x49]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4A]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4B]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4C]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4D]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4E]); 
  TEST_ASSERT_EQUAL_PTR(flashMemory, memoryTable[0x4F]); 
  
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x50]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x51]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x52]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x53]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x54]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x55]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x56]); 
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x57]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x58]);  // test is the corner memory space is noMemory
  
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x39]);  // test is the corner memory space is noMemory
  TEST_ASSERT_EQUAL_PTR(eepromMemory, memoryTable[0x40]); 
  TEST_ASSERT_EQUAL_PTR(eepromMemory, memoryTable[0x41]); 
  TEST_ASSERT_EQUAL_PTR(eepromMemory, memoryTable[0x42]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x43]);  // test is the corner memory space is noMemory
   
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x7E]);  // test is the corner memory space is noMemory
  TEST_ASSERT_EQUAL_PTR(cpuMemory, memoryTable[0x7F]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x80]);  // test is the corner memory space is noMemory
   
  free(cpu);
  free(cpuBlock);
  free(ramBlock);
  free(gpioBlock);
  free(eepromBlock);
  free(flashBlock);
}

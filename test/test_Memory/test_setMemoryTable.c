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
  assignNoMemoryToWholeMemoryTable(); //Assign noMemory to each row of memoryTable
}

void tearDown(void)
{
  
}


void test_setMemoryTable_given_set_ramMemory_from_startAddr_0x0_and_memSize_0x25(void){
  uint32_t startAddr = 0;
  uint8_t memSize = 0x25;
  
  setMemoryTable( ramMemory , startAddr , memSize );
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x0]);
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x1]);  //0x25/100 is < 1 , 
}

void test_setMemoryTable_given_set_ramMemory_from_startAddr_0x0_and_memSize_0x100(void){
  uint32_t startAddr = 0;
  uint16_t memSize = 0x100;
  
  setMemoryTable( ramMemory , startAddr , memSize );
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x0]);
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x1]); //0x100/0x100 = 1
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x2]);  
}

void test_setMemoryTable_given_set_ramMemory_from_startAddr_0x0_and_memSize_0x150(void){
  uint32_t startAddr = 0;
  uint16_t memSize = 0x100;
  
  setMemoryTable( ramMemory , startAddr , memSize );
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x0]);
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x1]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x2]); // 0x150/0x100 = 1
}

void test_setMemoryTable_given_set_ramMemory_from_startAddr_0x2700_and_memSize_0x5600(void){
  uint32_t startAddr = 0x2700;
  uint32_t memSize = 0x2900;  
  
  // 0x27 + 0x29 = 0x50, range from 0x27 to 0x50
  setMemoryTable( ramMemory , startAddr , memSize );
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x26]); 
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x27]);  //0x2700 / 0x100 = 0x27
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x50]);  //0x5000 / 0x100 = 0x50
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x51]); 
}


void test_setMemoryTable_given_set_ramMemory_at_0x2630_then_set_gpioMemory_at_0x2680_should_overwrite(void){

  setMemoryTable( ramMemory , 0x2500 , 0x130 );  //0x2500 + 0x130 + 0x2630
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x24]); 
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x25]);
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x26]);
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x27]); 
  
  setMemoryTable( gpioMemory , 0x2680 , 0x80);  //0x2680 + 0x80 + 0x2700
  TEST_ASSERT_EQUAL_PTR(ramMemory, memoryTable[0x25]);
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x26]);
  TEST_ASSERT_EQUAL_PTR(gpioMemory, memoryTable[0x27]); 
  TEST_ASSERT_EQUAL_PTR(noMemory, memoryTable[0x28]); 
}


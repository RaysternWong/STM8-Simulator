#include "unity.h"
#include "JPF.h"
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

void test_jpf_extmem(void){
  uint8_t instr[] = {0XAB, 0x33, 0x77, 0x88}; 
 
  TEST_ASSERT_EQUAL_INT8( 4, jpf_extmem(instr) );  
  TEST_ASSERT_EQUAL_INT32( 0x337788 , *pcToLoad );   
}

void test_jpf_longptr_e(void){
  uint8_t instr[] = {0XAB, 0x77, 0x88}; 
  MEM_WRITE_BYTE( 0x7788, 0x22);
  MEM_WRITE_BYTE( 0x7789, 0x55);
  MEM_WRITE_BYTE( 0x778A, 0x77);
 
  TEST_ASSERT_EQUAL_INT8( 4, jpf_longptr_e(instr) );  
  TEST_ASSERT_EQUAL_INT32( 0x225577 , *pcToLoad );   
}

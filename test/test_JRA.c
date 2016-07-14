#include "unity.h"
#include "JRA.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

/**
  Operation         PC = PC+lgth
                    PC <= PC + dst, if Condition is True
                    
      Description Unconditional relative jump. PC is updated by the signed addition of PC
      and dst. Control then passes to the statement addressed by the program
      counter. Else, the program continues normally.

*/

void test_jra_shortoff(void)
{
	SET_PC(0X7777);
  uint8_t instr[] = { 0xAB, 0x55};
  
  TEST_ASSERT_EQUAL_INT8( 2, jra_shortoff(instr) );  
  TEST_ASSERT_EQUAL_INT32( 0X7777 + 0x55 + 2 , PC ); 
}

void test_jra_shortoff_given_condition_is_not_true(void)
{
	SET_PC(0XFFFFF1);
  uint8_t instr[] = { 0xAB, 0x55};
  
  TEST_ASSERT_EQUAL_INT8( 2, jra_shortoff(instr) );  
  TEST_ASSERT_EQUAL_INT32( 0XFFFFF1 , PC ); 
}
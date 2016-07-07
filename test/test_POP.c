#include "unity.h"
#include "POP.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

//Please refer all the definations and marco in MCU_Operation.h

/**

POP $1234   | M(longmem) ← M(++SP)
POP CC      | CC ← M(++SP)
*/

uint16_t inputSP, sp_plus1, value;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  inputSP = 0x1122;
  sp_plus1 = inputSP + 1;
  SET_SP(inputSP);
  
  
  value = 0xEE;
  MEM_WRITE_BYTE( sp_plus1, value);
  

}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_pop_a(void)
{
  uint8_t instr[] = {0XAB};
  
  uint8_t length = pop_a(instr);
  TEST_ASSERT_EQUAL_INT8( value, A ); 
  TEST_ASSERT_EQUAL_INT8( inputSP +1 , SP ); // test is SP increament 1 time
  TEST_ASSERT_EQUAL_INT8( 1, length ); 
}

void test_pop_cc(void)
{
  uint8_t instr[] = {0XAB};
  
  uint8_t length = pop_cc(instr);
  TEST_ASSERT_EQUAL_INT8( value, CC ); 
  TEST_ASSERT_EQUAL_INT8( inputSP +1 , SP ); // test is SP increament 1 time
  TEST_ASSERT_EQUAL_INT8( 1, length ); 
}

void test_pop_longmem(void)
{
  uint8_t memMSB = 0x13;
  uint8_t memLSB = 0xDD;
  uint16_t longmem = 0x13DD;

  
  uint8_t instr[] = {0XAB, memMSB, memLSB};
  
  uint8_t length = pop_longmem(instr);
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(longmem) ); 
  TEST_ASSERT_EQUAL_INT8( inputSP +1 , SP ); // test is SP increament 1 time
  TEST_ASSERT_EQUAL_INT8( 3, length ); 
}


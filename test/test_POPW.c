#include "unity.h"
#include "POPW.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

//Please refer all the definations and marco in MCU_Operation.h

/**
POPW X      XH ← M(++SP)
            XL ← M(++SP)
*/

uint16_t inputSP, sp_plus1, sp_plus2 , value1, value2;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  inputSP = 0x1122;
  sp_plus1 = inputSP + 1;
  sp_plus2 = inputSP + 2;
  SET_SP(inputSP);
  
  
  value1 = 0xEE;
  value1 = 0xDD;
  MEM_WRITE_BYTE( sp_plus1, value1);
  MEM_WRITE_BYTE( sp_plus2, value2);
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_popw_x(void)
{
  uint8_t instr[] = {0XAB};
  
  uint8_t length = popw_x(instr);
  TEST_ASSERT_EQUAL_INT8( value1, XH ); 
  TEST_ASSERT_EQUAL_INT8( value2, XL ); 
  TEST_ASSERT_EQUAL_INT8( sp_plus2 , SP ); // test is SP increament 2 time
  TEST_ASSERT_EQUAL_INT8( 1, length ); 
}

void test_popw_y(void)
{
  uint8_t instr[] = {0XAB};
  
  uint8_t length = popw_y(instr);
  TEST_ASSERT_EQUAL_INT8( value1, YH ); 
  TEST_ASSERT_EQUAL_INT8( value2, YL ); 
  TEST_ASSERT_EQUAL_INT8( sp_plus2 , SP ); // test is SP increament 2 time
  TEST_ASSERT_EQUAL_INT8( 2, length ); 
}
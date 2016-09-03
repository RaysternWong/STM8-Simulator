#include "unity.h"
#include "PUSHW.h"
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

M(SP--) ← XL
M(SP--) ← XH

*/

uint16_t inputSP, inputSP_DEC;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(RAM_START_ADDR, 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  inputSP = 0x1122;
  inputSP_DEC = inputSP - 1;
  SET_SP(inputSP);
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}


/**
  PUSHW X

  M(SP--) ← XL
  M(SP--) ← XH
*/

void test_pushw_x(void)
{
  XH = 0xAA;
  XL = 0xBB;
  SET_X(0xAABB);
  
  uint8_t instr[] = {0XAB};

  uint8_t length = pushw_x(instr);
  TEST_ASSERT_EQUAL_INT8(0xBB, MEM_READ_BYTE(inputSP) ); 
  TEST_ASSERT_EQUAL_INT8(0xAA, MEM_READ_BYTE(inputSP_DEC) ); 
  TEST_ASSERT_EQUAL_INT16( inputSP-2 , SP ); // test is SP decreament 2 time
  TEST_ASSERT_EQUAL_INT8( 1, length ); 
}

void test_pushw_y(void)
{
  YH = 0xAA;
  YL = 0xBB;
  SET_Y(0xAABB);
  
  uint8_t instr[] = {0XAB};

  uint8_t length = pushw_y(instr);
  TEST_ASSERT_EQUAL_INT8(0xBB, MEM_READ_BYTE(inputSP) ); 
  TEST_ASSERT_EQUAL_INT8(0xAA, MEM_READ_BYTE(inputSP_DEC) ); 
  TEST_ASSERT_EQUAL_INT16( inputSP-2 , SP ); // test is SP decreament 2 time
  TEST_ASSERT_EQUAL_INT8( 2, length ); 
}
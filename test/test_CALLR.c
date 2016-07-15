#include "unity.h"
#include "CALLR.h"
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
CALLR label

          PC ← PC + 4
          M(SP--) ← PCL
          M(SP--) ← PCH
          PC ← PC + rr
*/



uint8_t value;
uint16_t inputSP, sp_minus1 ,sp_minus2;

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  inputSP = 0x1122;
  SET_SP(inputSP);
  sp_minus1 = inputSP - 1;
  sp_minus2 = inputSP - 2;
  
  PCH = 0x33;
  PCL = 0x44;
  
  value = 0xEE;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}


void test_callr_shortmem(void){
  uint8_t shortmem = 0x7d;
  uint8_t length   = 2;
  MEM_WRITE_BYTE(shortmem, value);
  
  SET_PC_WORD(0x3344);
  uint16_t outputPC = 0x3344 + value + length;
  
  uint8_t instr[] = {0XAB, shortmem}; 

  length = callr_shortmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x46, MEM_READ_BYTE(inputSP) );   // test is pcl store in the address , 44 + length
  TEST_ASSERT_EQUAL_INT8(0x33, MEM_READ_BYTE(sp_minus1) );  // test is pch store in the address ( sp decrement)
  TEST_ASSERT_EQUAL_INT8( sp_minus2, SP ); 
  TEST_ASSERT_EQUAL_INT16( outputPC , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 2, length );  
}

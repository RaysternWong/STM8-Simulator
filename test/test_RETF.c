#include "unity.h"
#include "RETF.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

/**
      PCE = (++SP)
      PCH = (++SP)
      PCL = (++SP)

      The PC wont change while execute this instruction,
      but store the value into pcToLoad,
      then only assign the value from pcToLoad to PC in executeOneInstructon()
*/


void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  pcToLoad = malloc(sizeof(uint32_t));
  *pcToLoad = 0;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_retf(void)
{
  uint16_t inputSP = 0x1122;
  uint16_t sp_plus1 = inputSP + 1;  //0x1123
  uint16_t sp_plus2 = inputSP + 2;  //0x1124
  uint16_t sp_plus3 = inputSP + 3;  //0x1125
  
  SET_SP(inputSP);
  MEM_WRITE_BYTE(sp_plus1, 0x77);
  MEM_WRITE_BYTE(sp_plus2, 0x88);
  MEM_WRITE_BYTE(sp_plus3, 0x99);
  
  uint8_t instr[] = {0XAB}; 
  
  uint8_t length = retf(instr);
  TEST_ASSERT_EQUAL_INT32( 0x778899 , *pcToLoad );   //PCE = 0x77, PCH = 0X88, PCL = 0X99
  TEST_ASSERT_EQUAL_INT16( sp_plus3, SP );  // is SP increment  2 time 
  TEST_ASSERT_EQUAL_INT8( 1, length );  
}
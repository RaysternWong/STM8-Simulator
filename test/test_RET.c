#include "unity.h"
#include "RET.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>


/**

RET                PCH ← M(++SP)    //POP
                   PCL ← M(++SP)    //POP

*/



void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_ret(void)
{
  uint16_t inputSP = 0x1122;
  uint16_t sp_plus1 = inputSP + 1;  //0x1123
  uint16_t sp_plus2 = inputSP + 2;  //0x1124
  
  SET_SP(inputSP);
  MEM_WRITE_BYTE(sp_plus1, 0x77);
  MEM_WRITE_BYTE(sp_plus2, 0x88);
  
  uint8_t instr[] = {0XAB}; 
  
  uint8_t length = ret(instr);
  TEST_ASSERT_EQUAL_INT16( 0x7788 , PC_WORD );   //PCH = 0X77, PCL = 0X88
  TEST_ASSERT_EQUAL_INT16( sp_plus2, SP );  // is SP increment  2 time 
  TEST_ASSERT_EQUAL_INT8( 1, length );  
}

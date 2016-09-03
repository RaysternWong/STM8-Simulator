#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

uint16_t inputSP, sp_minus1, sp_minus2;
void setUp(void)
{
  instantiateCPU();

  
   // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  inputSP = 0x1122;
  sp_minus1 = inputSP - 1;
  sp_minus2 = inputSP - 2;
  SET_SP(inputSP);
  
  pcToLoad = malloc(sizeof(uint32_t));
  *pcToLoad = 0;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock); 
  free(pcToLoad);
} 

/**

CALLF

    PC = PC+lgth
    (SP--) = PCL
    (SP--) = PCH
    (SP--) = PCE
    PC = dst
    
  The PC wont change while execute this instruction,
  but store the value into pcToLoad,
  then only assign the value from pcToLoad to PC in executeOneInstructon()
*/

void test_mcu_callf(void)
{
  uint32_t address   = 0x556677;
  uint8_t   length   = 4;
  
  SET_PC(0x12BBCC);
  
  mcu_callf( address,  length);    //12BBCC + 4 = 12BBDO
  TEST_ASSERT_EQUAL_INT8(0xD0, MEM_READ_BYTE(inputSP) );   // test is pcl store in the address
  TEST_ASSERT_EQUAL_INT8(0xBB, MEM_READ_BYTE(sp_minus1) );  // test is pch store in the address ( sp decrement)
  TEST_ASSERT_EQUAL_INT8(0x12, MEM_READ_BYTE(sp_minus2) );  // test is pce store in the address ( sp decrement)
  TEST_ASSERT_EQUAL_INT32( address , *pcToLoad );  
  TEST_ASSERT_EQUAL_INT8(inputSP -3, SP ); // test is sp decreament 3 time
}


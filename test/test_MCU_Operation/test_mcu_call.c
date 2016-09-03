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

CALL [$1234.w]
          PC← PC + 4
          M(SP--) ← PCL
          M(SP--) ← PCH
          PCH← M(longmem)
          PCL← M(longmem + 1)

    PC = PC+length
    (SP--) = PCL
    (SP--) = PCH
    PC = address
    
  The PC wont change while execute this instruction,
  but store the value into pcToLoad,
  then only assign the value from pcToLoad to PC in executeOneInstructon()
*/

void test_mcu_call(void)
{
  uint16_t currentPC = 0x12CC;
  uint16_t address   = 0x5555;
  uint8_t   length   = 4;
  
  SET_PC_WORD(currentPC);
  
  mcu_call( address,  length);    //12CC + 4 = 12DO
  TEST_ASSERT_EQUAL_INT8(0xD0, MEM_READ_BYTE(inputSP) );   // test is pcl store in the address
  TEST_ASSERT_EQUAL_INT8(0x12, MEM_READ_BYTE(sp_minus1) );  // test is pch store in the address ( sp decrement)
  TEST_ASSERT_EQUAL_INT16( address , *pcToLoad );  
  TEST_ASSERT_EQUAL_INT8( sp_minus2, SP ); 
}

void test_mcu_call_given_call_max_address(void)
{
  uint16_t currentPC = 0x12FF;
  uint16_t address   = 0xFFFF;
  uint8_t   length   = 4;
  
  SET_PC_WORD(currentPC);
  
  mcu_call( address,  length);    //0x12FF + 4 = 0x1303
  TEST_ASSERT_EQUAL_INT8(0x03, MEM_READ_BYTE(inputSP) );   // test is pcl store in the address
  TEST_ASSERT_EQUAL_INT8(0x13, MEM_READ_BYTE(sp_minus1) );  // test is pch store in the address ( sp decrement)
  TEST_ASSERT_EQUAL_INT16( address , *pcToLoad );  
  TEST_ASSERT_EQUAL_INT8( sp_minus2, SP ); 
}
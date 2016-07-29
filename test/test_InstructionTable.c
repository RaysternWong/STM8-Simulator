#include "unity.h"
#include <stdio.h>
#include <stdint.h>
#include "InstructionTable.h"
#include "ADDW.h"
#include "ADD.h"
#include "ADC.h"
#include "NEG.h"
#include "NEGW.h"
#include "SUBW.h"
#include "SBC.h"
#include "CPL.h"
#include "CPLW.h"
#include "INC.h"
#include "INCW.h"
#include "DEC.h"
#include "DECW.h"
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "CException.h"
#include <malloc.h>
#include "Description.h"


void setUp(void)
{
  instantiateCPU();
  
    // Set the ramMemory occupy the memoryTable from 0000 to 27FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0x17FFFF);
  setMemoryTable( ramMemory , 0 , 0x17FFFF); 

}

void tearDown(void)
{
   free(cpu);
   free(ramBlock);
}



void xtest1(void)
{
  uint8_t instsSets[] = {
    0x5b, 0x9,
    0x1C, 0x10,0x00
  };
  
  uint8_t *pc = instsSets;
  
  printf("%d\n",*pc);
  int a = firstOpcode[*pc](pc);
  printf("%d\n",a);
  pc+= firstOpcode[*pc](pc);
   
  pc+= firstOpcode[*pc](pc);
}

void test_getInstructionLength_ADDW_given_opcode_5B_should_return_2(void)
{
  uint8_t instsSets[] = {
    0x5b
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(2,ans);
}

void test_getInstructionLength_ADDW_given_opcode_72_F9_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x72, 0xF9
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_getInstructionLength_ADD_given_opcode_AB_should_return_2(void)
{
  uint8_t instsSets[] = {
    0xAB
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(2,ans);
}

void test_getInstructionLength_ADD_given_opcode_72_CB_MS_LS_should_return_4(void)
{
  uint8_t instsSets[] = {
    0x72, 0xCB, 0x10, 0x00
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(4,ans);
}

void test_getInstructionLength_ADD_given_opcode_90_EB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x90, 0xEB
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_getInstructionLength_ADD_given_opcode_91_DB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x91, 0xDB
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_getInstructionLength_ADD_given_opcode_92_DB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x92, 0xDB
  };

  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

// void xtest_getInstructionLength_given_instruction_is_not_in_table_should_throw_ERR_INSTRUCTION_NOT_IN_TABLE(void)
// {
  // CEXCEPTION_T err;
  
  // uint8_t instsSets[] = {
    // 0x00, 0x00, 0x00
  // };
  
  // Try{
    // int ans = getInstructionLength(instsSets);
    // TEST_FAIL_MESSAGE("Expected ERR_INSTRUCTION_NOT_IN_TABLE");
  // }Catch(err){
    // TEST_ASSERT_EQUAL_MESSAGE(ERR_INSTRUCTION_NOT_IN_TABLE, err, "Expected ERR_INSTRUCTION_NOT_IN_TABLE");
  // }
// }
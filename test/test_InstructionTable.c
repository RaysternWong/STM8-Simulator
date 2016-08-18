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
#include "NOP.h"
#include "CLR.h"
#include "CLRW.h"
#include "EXG.h"
#include "EXGW.h"
#include "MOV.h"
#include "RVF.h"
#include "CCF.h"
#include "RCF.h"
#include "SCF.h"
#include "SIM.h"
#include "RIM.h"
#include "TNZ.h"
#include "TNZW.h"
#include "BCP.h"
#include "TRAP.h"
#include "JP.h"
#include "JRA.h"
#include "JPF.h"
#include "JRXX.h"
#include "WFI.h"
#include "WFE.h"
#include "HALT.h"
#include "BREAK.h"
#include "IRET.h"
#include "BSET.h"
#include "BRES.h"
#include "BCPL.h"
#include "BCCM.h"
#include "BTJF.h"
#include "BTJT.h"
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

void test_executeInstructionThroughOpcode_ADDW_given_opcode_5B_should_return_2(void)
{
  uint8_t instsSets[] = {
    0x5b
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(2,ans);
}

void test_executeInstructionThroughOpcode_ADDW_given_opcode_72_F9_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x72, 0xF9
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_executeInstructionThroughOpcode_ADD_given_opcode_AB_should_return_2(void)
{
  uint8_t instsSets[] = {
    0xAB
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(2,ans);
}

void test_executeInstructionThroughOpcode_ADD_given_opcode_72_CB_MS_LS_should_return_4(void)
{
  uint8_t instsSets[] = {
    0x72, 0xCB, 0x10, 0x00
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(4,ans);
}

void test_executeInstructionThroughOpcode_ADD_given_opcode_90_EB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x90, 0xEB
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_executeInstructionThroughOpcode_ADD_given_opcode_91_DB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x91, 0xDB
  };
  
  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_executeInstructionThroughOpcode_ADD_given_opcode_92_DB_should_return_3(void)
{
  uint8_t instsSets[] = {
    0x92, 0xDB
  };

  int ans = executeInstructionThroughOpcode(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}

void test_executeInstructionThroughOpcode_given_HALT_should_throw_ERR_HALT(void){
  CEXCEPTION_T err;

  uint8_t instsSets[] = {
    0x8E
  };
  
  Try{
    int ans = executeInstructionThroughOpcode(instsSets);

    TEST_FAIL_MESSAGE("Expected ERR_HALT");
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_HALT, err, "Expected ERR_HALT");
  }
}

void test_executeInstructionThroughOpcode_given_WFI_should_throw_ERR_WFI(void){
  CEXCEPTION_T err;

  uint8_t instsSets[] = {
    0x8F
  };
  
  Try{
    int ans = executeInstructionThroughOpcode(instsSets);

    TEST_FAIL_MESSAGE("Expected ERR_WFI");
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_WFI, err, "Expected ERR_WFI");
  }
}

void test_executeInstructionThroughOpcode_given_WFE_should_throw_ERR_WFE(void){
  CEXCEPTION_T err;

  uint8_t instsSets[] = {
    0X72, 0x8F
  };
  
  Try{
    int ans = executeInstructionThroughOpcode(instsSets);

    TEST_FAIL_MESSAGE("Expected ERR_WFE");
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_WFE, err, "Expected ERR_WFE");
  }
}

void test_executeInstructionThroughOpcode_given_BREAK_should_throw_ERR_BREAK(void){
  CEXCEPTION_T err;

  uint8_t instsSets[] = {
    0x8B
  };
  
  Try{
    int ans = executeInstructionThroughOpcode(instsSets);

    TEST_FAIL_MESSAGE("Expected ERR_BREAK");
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_BREAK, err, "Expected ERR_BREAK");
  }
}
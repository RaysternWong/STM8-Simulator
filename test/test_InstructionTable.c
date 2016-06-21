#include "unity.h"
#include <stdio.h>
#include <stdint.h>
#include "InstructionTable.h"
#include "ADDW.h"
#include "ADD.h"

void setUp(void)
{
}

void tearDown(void)
{
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
    0x72, 0xf9
  };
  
  int ans = getInstructionLength(instsSets);
  
  TEST_ASSERT_EQUAL(3,ans);
}
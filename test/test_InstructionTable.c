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



void test1(void)
{
  uint8_t instsSets[] = {
    0x5b, 0x9,
    0x1C, 0x10,0x01
  };
  
  uint8_t *pc = instsSets;
  pc+= firstOpcode[*pc](pc);
  pc+= firstOpcode[*pc](pc);
}
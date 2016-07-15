#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include <malloc.h>
#include "Memory.h"
#include "ErrorObject.h"

void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
  free(cpu);
}

//#define SET_PC(extend)       setBigEndianExt(&PCE, extend)
void test_setBigEndianExt_given_PC(void){
  
  SET_PC(0xABCCD5);
  
  TEST_ASSERT_EQUAL_INT32(0xABCCD5, PC);
}






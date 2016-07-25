#include "unity.h"
#include "MCU_Operation.h"
#include "ErrorObject.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


void setUp(void){
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
 
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/**

  NEG ([$1234.w],X)    M(M(longmem) + X) ← 00 - M(M(longmem) + X)
               
*/

void test_mcu_negw_set_negative_flag_carry_flag(void){

  MEM_WRITE_BYTE(0x1122,0x71);
  MEM_WRITE_BYTE(0x1123,0x00);
  mcu_neg(0x1122);
  
  TEST_ASSERT_EQUAL_INT8(0x8F, MEM_READ_BYTE(0x1122));

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result > 0
}



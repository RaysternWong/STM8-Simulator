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

void test_mcu_neg_set_negative_flag_carry_flag(void){
  SET_X(0x1133);
  MEM_WRITE_BYTE(X,0x71);
  mcu_neg(X);
  
  TEST_ASSERT_EQUAL_INT8(0x8F, MEM_READ_BYTE(X));

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result > 0
}

void test_mcu_neg_set_zero_flag(void){
  uint16_t addr = 0x2255;
  MEM_WRITE_BYTE(addr,0);
  mcu_neg(addr);
  
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(addr));

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

/*

Set if there is an arithmetic overflow on the 8-bit representation of the
result. The V bit will set when the content of "dst" was $80 (-128) prior to
the NEG operation, cleared otherwise.

*/
void test_mcu_neg_set_overflow_flag(void){
  uint16_t addr = 0x2255;
  MEM_WRITE_BYTE(addr,0x80);
  mcu_neg(addr);
  
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(addr));

  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // result > 0
}

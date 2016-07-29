#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
}

void tearDown(void)
{
  free(cpu);
}

// A = A - 1 - C
void test_mcu_sbc_given_C_is_0(void){
  A = 0x09;
  C = 0;
  mcu_sbc(0x01);

  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

// A = A - 1 - C
void test_mcu_sbc_given_C_is_1(void){
  A = 0x09;
  C = 1;
  mcu_sbc(0x01);

  TEST_ASSERT_EQUAL_INT8(0x07, A);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


void test_mcu_sbc_given_a_equal_9_than_sub_9_should_get_a_equal_0_and_zero_flag_1(void){
  A = 0x09;
  mcu_sbc(0x09);
  
  TEST_ASSERT_EQUAL_INT8(0x00, A);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}
 

void test_mcu_sbc_given_a_equal_0_than_sub_1_should_get_A_equal_neg1_and_set_N_flag_and_C_flag(void){
  A = 0x00;
  mcu_sbc(0x01);
  
  TEST_ASSERT_EQUAL_INT8(-0x01, A);

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C); // Set if a borrow request occurred from bit 7
}

/** 0xFE - 0x7F = 0x7F , V = 1, N = 1
*
*   Overflow occurs if 
*    (-A) - (+B) = +C
*
*        1111   1110   FE  (-Ve)
*   -    0111   1111   7F  (+Ve)
*--------------------
*        0111   1111   7F  (+Ve)
*---------------------
*
*/
void test_mcu_sbc_given_a_equal_40_than_sub_40_should_get_A_equal_E0_and_overfow_flag_1_neg_flag_1(void){
  A = 0xFE;
  mcu_sbc(0x7F);

  TEST_ASSERT_EQUAL_INT8(0x7F, A);
  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


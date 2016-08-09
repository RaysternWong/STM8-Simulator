#include "unity.h"
#include "MCU_Operation.h"
#include "ErrorObject.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
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

// 0xFFFF + 0xF122 = 0x0EDD
void test_mcu_subw_given_x_equal_ffff_than_subw_f122_should_get_x_equal_0edd_and_all_flags_are_0(void){

  SET_X(0xFFFF);
  mcu_subw(&XH, 0xF122);
  
  TEST_ASSERT_EQUAL_INT16(0x0EDD, X);


  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


void test_mcu_subw_given_x_equal_1111_than_subw_1111_should_get_x_equal_0_and_zero_flag_1(void){
  
  SET_X(0x1111);
  mcu_subw(&XH, 0x1111);
  
  TEST_ASSERT_EQUAL_INT16(0, X);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}
 

void test_mcu_subw_given_neg_flag_1(void){

  SET_X(0xFFFF);
  mcu_subw(&XH, 0x1FFF);
  
  TEST_ASSERT_EQUAL_INT16(0xE000, X);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1 
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

/**
*
*   Overflow occurs if 
*    (-A) - (+B) = +C
*
*        1000 0000 0000 0000 | 0x8000  (-Ve)
*   -    0000 0001 0001 0001 | 0x0111  (+Ve)
*----------------------------
*        0111 1110 1110 1111  | 0x7EEF (+Ve)
*---------------------------
*
*   V = 1 , because meet the condition
*   H = 1 , Set if a carry occurred from bit 7, cleared otherwise.
*/
void test_mcu_subw_given_set_2_flag(void){
  
  SET_X(0x8000);
  mcu_subw(&XH, 0x0111);
  
  TEST_ASSERT_EQUAL_INT16(0x7EEF, X);

  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(1, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


void test_mcu_subw_given_set_c_n_flag(void){
  
  SET_X(0x0000);
  mcu_subw(&XH, 0x0111);
  
  TEST_ASSERT_EQUAL_INT16(0xFEEF, X);

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(1, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N); // bit 15 is 1 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(1, C); //Set if a borrow request occurred from bit 15, cleared otherwise.
}

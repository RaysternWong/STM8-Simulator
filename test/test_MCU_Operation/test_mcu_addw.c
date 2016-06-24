#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"

#define A   cpu.accA    //Accumulator
#define X   cpu.index_X //Index registers X 
#define Y   cpu.index_Y //Index registers Y 
#define SP  cpu.sp      //Stack pointer
#define CC  cpu.ccR     //Condition Code


void setUp(void)
{
  clearConditionCodeRegister(&(CC));
}

void tearDown(void)
{
}

// 0x0 + 0x1 = 0x1
void test_mcu_addw_given_x_equal_0_than_add_1_should_get_x_equal_0x01_and_all_flags_are_0(void){

  X = 0x00;
  mcu_addw(&X, 0x01);
  
  TEST_ASSERT_EQUAL_INT8(0x01, X);
  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

// 0x0 + 0x0 = 0x0 , Z = 1
void test_mcu_addw_given_a_equal_0_than_add_0_should_get_A_equal_0_and_zero_flag_1(void){
  Y = 0x00;
  mcu_addw(&Y, 0x00);
  
  TEST_ASSERT_EQUAL_INT8(0x00, Y);
  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(1, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}
 
/** -0x0001 + 0x0 = -0x01 , N = 1
*
* negative flag set to 1, becauser result is negative, which R7 (signing bit) is 1
*/
void test_mcu_addw_given_X_equal_neg1_than_add_0_should_get_Xequal_neg1_and_neg_flag_1_overflow_flag_1(void){
  X = -0x0001;
  
  mcu_addw(&X, 0x00);
  
  TEST_ASSERT_EQUAL_INT8(-0x0001, X);

  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(1, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

/** 0xFF80 + 0x0080 = 0x00, H = 1, C = 1 
*
*        1111   1111  1000  0000   0xFF80
*   +    0000   0000  1000  0000   0x0080
*--------------------------------
*    1   0000   0000  0000  0000
*--------------------------------
*
*  half carry flag is set to 1, because that is carry from bit 7 to bit 8
*  carry flag is set to 1, because that is carry from bit 15 to bit 16
*  zero  flag is set to 1
*/
void test_mcu_addw_given_x_equal_FF80_than_add_0080_should_get_x_equal_00_and_half_carry_flag_1_carry_flag_1_zero_flag_1(void){
  X = 0xFF80;
  mcu_addw(&X, 0x0080);
  TEST_ASSERT_EQUAL_INT8(0x0000, X);

  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(1, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(1, CC.Z);
  TEST_ASSERT_EQUAL(1, CC.C);
}

/** 0x4000 + 0x4000 = 0x8000 , V = 1, N = 1
*
*   In math arithmatic rule
*   1. Adding two positive numbers must give a positive result
*  	2. Adding two negative numbers must give a negative result
*
*   Overflow occurs if 
*
*    (+A) + (+B) = −C
*    (−A) + (−B) = +C
*
*        0100   0000  0000  0000  0x4000  (+Ve)
*   +    0100   0000  0000  0000  0x4000  (+Ve)
*--------------------
*        1000   0000  0000  0000  0x8000  (-Ve)
*---------------------
*
*  40 is positive number, because bit 7 is 0.
*  80 is negative number, because bit 7 is 1 
*
* overflow flag is set to 1, because sum of 2 positive number get negative result
* negative flag is set to 1, because R7 (signing bit) is 1
*/
void test_mcu_addw_given_x_equal_40_than_add_40_should_get_A_equal_E0_and_overfow_flag_1_neg_flag_1(void){
  X = 0x4000;
  mcu_addw(&X, 0x4000);

  TEST_ASSERT_EQUAL_INT8(0x8000, X);
  
  TEST_ASSERT_EQUAL(1, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(1, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}
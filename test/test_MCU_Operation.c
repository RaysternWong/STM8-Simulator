#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"

#define A   cpu.accA //Accumulator
#define CC  cpu.ccR  //Condition Code

#define A0  (A & 0X01)
#define A1  (A & 0X02) >> 1
#define A2  (A & 0X04) >> 2
#define A3  (A & 0X08) >> 3
#define A4  (A & 0X10) >> 4
#define A5  (A & 0X20) >> 5
#define A6  (A & 0X40) >> 6
#define A7  (A & 0X80) >> 7

void setUp(void)
{
  clearConditionCodeRegister(&(CC));
}

void tearDown(void)
{
}


// 0x0 + 0x1 = 0x1
void test_mcu_add_given_a_equal_0_than_add_1_should_get_A_equal_0x01_and_all_flags_are_0(void){
  A = 0x00;
  mcu_add(0x01);
  
  TEST_ASSERT_EQUAL_INT8(0x01, A);
  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

// 0x0 + 0x0 = 0x0 , Z = 1
void test_mcu_add_given_a_equal_0_than_add_0_should_get_A_equal_0_and_zero_flag_1(void){
  A = 0x00;
  mcu_add(0x00);
  
  TEST_ASSERT_EQUAL_INT8(0x00, A);
  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(1, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}
 
/** -0x01 + 0x0 = -0x01 , N = 1 , v =1 
*
*
* (OF) overflow flag indicates that result is too large to fit in the 8-bit destination operand
*  condtion 1. the sum of two positive signed operands exceeds 127 (0x7F).
*  condtion 2.the difference of two negative operands is less than -128.
*
* overflow flag is set to 1, because it meet condtion 1
* negative flag set to 1, becauser result is negative, which R7 (signing bit) is 1
*/
void test_mcu_add_given_a_equal_neg1_than_add_0_should_get_A_equal_neg1_and_neg_flag_1_overflow_flag_1(void){
  A = -0x01;
  mcu_add(0x00);
  
  TEST_ASSERT_EQUAL_INT8(-0x01, A);

  TEST_ASSERT_EQUAL(1, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(1, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

/** 0x0F + 0x0F = 0x1E, H = 1 
*
*        0000   1111     0F
*   +    0000   1111     0F
*--------------------
*        0001   1110     1E
*---------------------
*
*  half carry flag is set to 1, because that is carry from bit 3 to bit 4
*/
void test_mcu_add_given_a_equal_F_than_add_F_should_get_A_equal_1E_and_half_carry_flag_1(void){
  A = 0x0F;
  mcu_add(0x0F);
  
  TEST_ASSERT_EQUAL_INT8(0x1E, A);

  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(1, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

/** 0x0F + 0x01 = 0x10, H = 1 
*
*        0000   1111     0F
*   +    0000   0001     01
*--------------------
*        0001   0000     10
*---------------------
*
*  half carry flag is set to 1, because that is carry from bit 3 to bit 4
*/
void test_mcu_add_given_a_equal_F_than_add_1_should_get_A_equal_10_and_half_carry_flag_1(void){
  A = 0x0F;
  mcu_add(0x01);
  
  TEST_ASSERT_EQUAL_INT8(0x10, A);

  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(1, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(0, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}

/** 0xF0 + 0xF0 = 0xE0, C = 1 , N = 1
*
*        1111   0000    F0
*   +    1111   0000    F0
*--------------------
*    1   1110   0000    E0
*---------------------
*
*  carry flag is set to 1, because that is carry from bit 7 to bit 8
*  negative flag is set to 1, because R7 is 1
*/
void test_mcu_add_given_a_equal_F0_than_add_F0_should_get_A_equal_E0_and_carry_flag_1_neg_flag_1(void){
  A = 0xF0;
  mcu_add(0xF0);
  
  TEST_ASSERT_EQUAL_INT8(0xE0, A);

  TEST_ASSERT_EQUAL(0, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(1, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(1, CC.C);
}

/** 0xFF + 0x00 = 0xFF , V = 1, N = 1
*
*
* (OF) overflow flag indicates that result is too large to fit in the 8-bit destination operand
*  condtion 1. the sum of two positive signed operands exceeds 127 (0x7F).
*  condtion 2.the difference of two negative operands is less than -128.
*
* overflow flag is set to 1, because it meet condtion 1
* negative flag is set to 1, because R7 (signing bit) is 1
*/
void test_mcu_add_given_a_equal_7F_than_add_7F_should_get_A_equal_E0_and_overfow_flag_1_carry_flag_1(void){
  A = 0xFF;
  mcu_add(0x00);
  
  TEST_ASSERT_EQUAL_INT8(0xFF, A);

  TEST_ASSERT_EQUAL(1, CC.V);
  TEST_ASSERT_EQUAL(0, CC.l1);
  TEST_ASSERT_EQUAL(0, CC.H);
  TEST_ASSERT_EQUAL(0, CC.l0);
  TEST_ASSERT_EQUAL(1, CC.N);
  TEST_ASSERT_EQUAL(0, CC.Z);
  TEST_ASSERT_EQUAL(0, CC.C);
}
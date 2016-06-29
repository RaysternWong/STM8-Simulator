#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>

#define A   cpu->a           //Accumulator

#define XH   cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL   cpu->xl           //least significant byte of the X index register (1 byte)

#define YH   cpu->yh           //most significant byte of the X index register  (1 byte)
#define YL   cpu->yl           //least significant byte of the X index register (1 byte)

#define SPH   cpu->sph          //most significant byte of the X index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the X index register (1 byte)

#define V   (cpu->ccr).bits.v   //overFlow
#define L1  (cpu->ccr).bits.l1  //interrupt mask level 1
#define H   (cpu->ccr).bits.h   //half cary
#define L0  (cpu->ccr).bits.l0  //interrupt mask level 0
#define N   (cpu->ccr).bits.n   //negative
#define Z   (cpu->ccr).bits.z   //zero
#define C   (cpu->ccr).bits.c   //carry



void setUp(void)
{
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
}

void tearDown(void)
{
  free(cpu);
}

// 0x0 + 0x1 = 0x1
void test_mcu_addw_given_x_equal_0_than_add_1_should_get_x_equal_0x01_and_all_flags_are_0(void){

  XH = 0x00;
  XL = 0x00;
  mcu_addw(&XH, &XL, 0x01);
  
  TEST_ASSERT_EQUAL_INT8(0x00, XH);
  TEST_ASSERT_EQUAL_INT8(0x01, XL);

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

// 0x0 + 0x0 = 0x0 , Z = 1
void xtest_mcu_addw_given_a_equal_0_than_add_0_should_get_A_equal_0_and_zero_flag_1(void){

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}
 
/** -0x0001 + 0x0 = -0x01 , N = 1
*
* negative flag set to 1, becauser result is negative, which R7 (signing bit) is 1
*/
void xtest_mcu_addw_given_X_equal_neg1_than_add_0_should_get_Xequal_neg1_and_neg_flag_1_overflow_flag_1(void){


  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
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
void xtest_mcu_addw_given_x_equal_FF80_than_add_0080_should_get_x_equal_00_and_half_carry_flag_1_carry_flag_1_zero_flag_1(void){


  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(1, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(1, C);
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
* negative flag is set to 1, because R15 (signing bit) is 1
*/
void xtest_mcu_addw_given_x_equal_40_than_add_40_should_get_A_equal_E0_and_overfow_flag_1_neg_flag_1(void){

  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}
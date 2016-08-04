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


void test_mcu_cp_make_Z_to_1(void){
  mcu_cp(0x3,0x3);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z); // 3 -3 = 0
  TEST_ASSERT_EQUAL(0, C);
}

void test_mcu_cp_make_N_to_1(void){
  mcu_cp(0x83,0x03);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(1, N); 
  TEST_ASSERT_EQUAL(0, Z); //0x80 , bit7 is 1
  TEST_ASSERT_EQUAL(0, C);
}

void test_mcu_cp_make_C_to_1(void){
  mcu_cp(0x53,0x73);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(1, N); //bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(1, C); // 73 greater than 53
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
void test_mcu_cp_make_V_to_1(void){
  mcu_cp(0xFE,0x7F);
  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}


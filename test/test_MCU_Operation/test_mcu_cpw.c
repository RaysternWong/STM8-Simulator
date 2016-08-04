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

void test_mcu_cpw_make_Z_to_1(void){
  mcu_cpw(0x3333,0x3333);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z); // 3 -3 = 0
  TEST_ASSERT_EQUAL(0, C);
}

void test_mcu_cpw_make_N_to_1(void){
  mcu_cpw(0x8322,0x0322);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(1, N); 
  TEST_ASSERT_EQUAL(0, Z); //0x80 , bit15 is 1
  TEST_ASSERT_EQUAL(0, C);
}

void test_mcu_cpw_make_C_to_1(void){
  mcu_cpw(0x5300,0x7300);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(1, N); //bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(1, C); // 73 greater than 53
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
void test_mcu_cpw_make_V_to_1(void){
  
  SET_X(0x8000);
  mcu_cpw(X, 0x0111);
  
  TEST_ASSERT_EQUAL(1, V);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}



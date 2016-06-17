#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"


#define CCR cpu.ccR


CPU cpu;

void setUp(void)
{
  clearConditionCodeRegister(&(cpu.ccR));
}

void tearDown(void)
{
}



void test_mcu_add_given_a_equal_0_than_add_1_should_get_all_flags_are_0(void){
  
  cpu.accA = 0x00;
  mcu_add(&cpu, 0x01);
  
  TEST_ASSERT_EQUAL(0x01, cpu.accA);
  
  TEST_ASSERT_EQUAL(0x00, CCR.V);
  TEST_ASSERT_EQUAL(0x00, CCR.l1);
  TEST_ASSERT_EQUAL(0x00, CCR.H);
  TEST_ASSERT_EQUAL(0x00, CCR.l0);
  TEST_ASSERT_EQUAL(0x00, CCR.N);
  TEST_ASSERT_EQUAL(0x00, CCR.Z);
  TEST_ASSERT_EQUAL(0x00, CCR.C);
}

void test_mcu_add_given_a_equal_0_than_add_0_should_get_zero_flag_1(void){
  
  cpu.accA = 0x00;
  mcu_add(&cpu, 0x00);
  
  TEST_ASSERT_EQUAL(0x00, cpu.accA);
  
  TEST_ASSERT_EQUAL(0x00, CCR.V);
  TEST_ASSERT_EQUAL(0x00, CCR.l1);
  TEST_ASSERT_EQUAL(0x00, CCR.H);
  TEST_ASSERT_EQUAL(0x00, CCR.l0);
  TEST_ASSERT_EQUAL(0x00, CCR.N);
  TEST_ASSERT_EQUAL(1, CCR.Z);
  TEST_ASSERT_EQUAL(0x00, CCR.C);
}
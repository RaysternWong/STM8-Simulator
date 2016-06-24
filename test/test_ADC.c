#include "unity.h"
#include "ADC.h"
#include <stdio.h>
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define A   cpu.accA       //Accumulator
#define X   cpu.index_X    //Index registers X  
#define Y   cpu.index_Y    //Index registers X  
#define SP  cpu.sp         //Index registers X  


void setUp(void)
{
}

void tearDown(void)
{
}


// 0x01 + 0x05 = 0x06
void test_adc_a_ht_byte_given_A_0x01_mcu_memory_return_0x05_should_get_0x06_and_return_2(void)
{
  A = 0x01;
  uint8_t instr[] = {0XAB, 0X05};
  
  int ans = adc_a_ht_byte(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(2, ans);
}

void test_adc_a_shortmem_given_A_0x01_mcu_memory_return_0x02_should_get_0x03_and_return_2(void)
{
  A = 0x01;
  uint8_t instr[] = {0XBB, 10};
  mcu_memory[10] = 0x02;
  
  int ans = adc_a_shortmem(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, ans);
}

void test_adc_a_longmem_given_A_0x01_mcu_memory_return_0x02_should_get_0x03_and_return_3(void)
{
  A = 0x01;
  uint8_t instr[] = {0XCB, 10, 00};
  mcu_memory[1000] = 0x02;
  
  int ans = adc_a_longmem(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(3, ans);
}

void test_adc_a_x_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_1(void)
{
  A = 0x01;
  X = 100;
  uint8_t instr[] = {0XFB, 5};
  mcu_memory[100] = 0x40;
  
  int ans = adc_a_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(1, ans);
}

void test_adc_a_shortoff_x_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_2(void)
{
  A = 0x01;
  X = 100;
  uint8_t instr[] = {0XEB, 5};
  mcu_memory[105] = 0x40;
  
  int ans = adc_a_shortoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(2, ans);
}

void test_adc_a_longoff_x_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_3(void)
{
  A = 0x01;
  X = 100;
  uint8_t instr[] = {0XDB, 10, 00};
  mcu_memory[1100] = 0x40;
  
  int ans = adc_a_longoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(3, ans);
}

void test_adc_a_y_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_2(void)
{
  A = 0x01;
  Y = 100;
  uint8_t instr[] = {0XFB, 5};
  mcu_memory[100] = 0x40;
  
  int ans = adc_a_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(2, ans);
}

void test_adc_a_shortoff_y_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_3(void)
{
  A = 0x01;
  Y = 100;
  uint8_t instr[] = {0XEB, 5};
  mcu_memory[105] = 0x40;
  
  int ans = adc_a_shortoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(3, ans);
}

void test_adc_a_longoff_y_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_4(void)
{
  A = 0x01;
  Y = 100;
  uint8_t instr[] = {0XDB, 10, 00};
  mcu_memory[1100] = 0x40;
  
  int ans = adc_a_longoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(4, ans);
}

void test_adc_a_shortoff_sp_given_A_0x01_mcu_memory_return_0x40_should_get_0x41_and_return_3(void)
{
  A = 0x01;
  SP = 100;
  uint8_t instr[] = {0X1B, 5};
  mcu_memory[105] = 0x40;
  
  int ans = adc_a_shortoff_sp(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x41, A);
  TEST_ASSERT_EQUAL(2, ans);
}
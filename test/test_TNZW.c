#include "unity.h"
#include "TNZW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}


void test_tnzw_x(void)
{
  SET_X(0);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL(1, tnzw_x(instr));

  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(1, Z); // X is 0
}

void test_tnzw_y(void)
{
  SET_Y(0x8000);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL(2, tnzw_y(instr));

  TEST_ASSERT_EQUAL(1, N); // Y is negative , because bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnzw_y_given_y_neither_zero_or_negative(void)
{
  SET_Y(0x789A);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL(2, tnzw_y(instr));

  TEST_ASSERT_EQUAL(0, N); //Y is neither zero or negative
  TEST_ASSERT_EQUAL(0, Z); 
}
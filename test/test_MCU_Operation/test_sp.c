#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
  free(cpu);
}

void test_sp_decrement(void){
  SET_SP(0x3344);
  sp_decrement();
  TEST_ASSERT_EQUAL_INT16(0x3343, SP);
}

void test_sp_increment(void){
  SET_SP(0x3344);
  sp_increment();
  TEST_ASSERT_EQUAL_INT16(0x3345, SP);
}
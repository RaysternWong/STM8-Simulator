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

//#define SET_X(word)  setBigEndianWord(&XH, word)
void test_setBigEndianWord_given_X(void){
  
  SET_X(0xABCC);
  
  TEST_ASSERT_EQUAL_INT32(0xABCC, X);
}

//#define SET_Y(word)  setBigEndianWord(&YH, word)
void test_setBigEndianWord_given_Y(void){
  
  SET_Y(0xABCC);
  
  TEST_ASSERT_EQUAL_INT32(0xABCC, Y);
}

//#define SET_SP(word)  setBigEndianWord(&SPH, word)
void test_setBigEndianWord_given_SP(void){
  
  SET_SP(0xABCC);
  
  TEST_ASSERT_EQUAL_INT32(0xABCC, SP);
}

//#define SET_PC_WORD(word)  setBigEndianWord(&PCH, word)
void test_setBigEndianWord_given_PC_WORD(void){
  
  SET_PC_WORD(0xABCC);
  
  TEST_ASSERT_EQUAL_INT32(0xABCC, PC_WORD);
}


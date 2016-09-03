#include "unity.h"
#include "MCU_Operation.h"
#include "ErrorObject.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>



void setUp(void){
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
  gpioInit(0x0, 0x17FFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_LOAD_BYTE_TO_REG_given_load_0xBB_to_A(void){
  
  LOAD_BYTE_TO_REG(A, 0xBB);
  TEST_ASSERT_EQUAL_INT8(0xBB, A);
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(1, N); // bit 7 is 1
}

void test_LOAD_WORD_TO_REG_given_load_0x2233_to_X(void){
  
  LOAD_WORD_TO_REG(XH, 0x2233);
  TEST_ASSERT_EQUAL_INT8(0x2233, X);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
}


void test_LOAD_WORD_TO_REG_given_load_0_to_X(void){
  
  LOAD_WORD_TO_REG(XH, 0);
  TEST_ASSERT_EQUAL_INT8(0, X);
  TEST_ASSERT_EQUAL_INT8(1, Z); // value is 0
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_BYTE_TO_MEM_given_load_0x55_to_shortAddress(void){
  uint8_t shortAddr = 0x12;
  
  LOAD_BYTE_TO_MEM( shortAddr , 0x55);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(shortAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_BYTE_TO_MEM_given_load_0x55_to_longAddress(void){
  uint16_t longAddr = 0x1234;
  
  LOAD_BYTE_TO_MEM( longAddr , 0x55);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_BYTE_TO_MEM_given_load_0x55_to_extendAddress(void){
  uint32_t extendAddr = 0x123456;
  
  LOAD_BYTE_TO_MEM( extendAddr , 0x55);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(extendAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_WORD_TO_MEM_given_load_0x5588_to_shortAddress(void){
  uint8_t shortAddr = 0x12;
  
  LOAD_WORD_TO_MEM( shortAddr , 0x5588);
  TEST_ASSERT_EQUAL_INT8(0x5588, MEM_READ_WORD(shortAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_WORD_TO_MEM_given_load_0x5588_to_longAddress(void){
  uint16_t longAddr = 0x1234;
  
  LOAD_WORD_TO_MEM( longAddr , 0x5588);
  TEST_ASSERT_EQUAL_INT8(0x5588, MEM_READ_WORD(longAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_LOAD_WORD_TO_MEM_given_load_0x5588_to_extendAddress(void){
  uint32_t extendAddr = 0x123456;
  
  LOAD_WORD_TO_MEM( extendAddr , 0x5588);
  TEST_ASSERT_EQUAL_INT8(0x5588, MEM_READ_WORD(extendAddr) );
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

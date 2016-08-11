#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>



void setUp(void){
}

void tearDown(void){

}

void test_swap_byte_given_0xF0(void){
  uint8_t byte = 0xF0;
  TEST_ASSERT_EQUAL_INT8(0x0F, SWAP_BYTE(byte));
}


void test_swap_byte_given_0x55(void){
  TEST_ASSERT_EQUAL_INT8(0x55, SWAP_BYTE(0x55));
}


void test_swap_byte_given_0x5C(void){
  TEST_ASSERT_EQUAL_INT8(0xC5, SWAP_BYTE(0x5C));
}


void test_swap_word_given_0x00FF(void){
  TEST_ASSERT_EQUAL_INT16(0x00FF, SWAP_WORD(0xFF00));
}

void test_swap_word_given_0x2233(void){
  TEST_ASSERT_EQUAL_INT16(0x2233, SWAP_WORD(0x3322));
}

void test_swap_word_given_0x5555(void){
  TEST_ASSERT_EQUAL_INT16(0x5555, SWAP_WORD(0x5555));
}




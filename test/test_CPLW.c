#include "unity.h"
#include "CPLW.h"
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
  clearConditionCodeRegister(&(cpu->ccr));  
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_cplw_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, cplw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0xEFD4, X);  // 0xFFFF - 0x102b = 0xEFD4
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  
}

void test_cplw_x_set_N_flag(void){
  SET_X(0X0FFF);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, cplw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0xF000, X);  // 0xFFFF - 0xFFF= 0xF000
  
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  
}

void test_cplw_x_set_Z_flag(void){
  SET_X(0XFFFF);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(1, cplw_x(instr));
  TEST_ASSERT_EQUAL_INT8( 0, X);  // 0xFFFF - 0xFFFF= 0
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(1, C);  
}

void test_cplw_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  TEST_ASSERT_EQUAL_INT8(2, cplw_y(instr));
  TEST_ASSERT_EQUAL_INT8( 0xEFD4, Y); // 0 - 0x102b = 0xEFD5
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);   
}
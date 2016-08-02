#include "unity.h"
#include "LD.h"
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
  A = 0xAE;
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/*

    LD A,($12,SP)     | A ← M(SP+shortoff)

    LD ($12,SP),A     |M(SP+shortoff) ← A

    LD A, XH          |A ← XH

*/


void test_ld_xl_a(void){
  A = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(1, ld_xl_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, XL);
}

void test_ld_a_xl(void){
  XL = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(1, ld_a_xl(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
}

void test_ld_yl_a(void){
  A = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_yl_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, YL);
}

void test_ld_a_yl(void){
  YL = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_yl(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
}

void test_ld_xh_a(void){
  A = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(1, ld_xh_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, XH);
}

void test_ld_a_xh(void){
  XH = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(1, ld_a_xh(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
}

void test_ld_yh_a(void){
  A = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_yh_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, YH);
}

void test_ld_a_yh(void){
  YH = 0x88;
  uint8_t instr[] = {0XBB};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_yh(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
}
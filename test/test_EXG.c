#include "unity.h"
#include "EXG.h"
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

void test_exg_a_xl(void){
  A = 0x55;
  XL = 0x88;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, exg_a_xl(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
  TEST_ASSERT_EQUAL_INT8(0x55, XL);
}

void test_exg_a_yl(void){
  A = 0x55;
  YL = 0x88;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, exg_a_yl(instr));
  TEST_ASSERT_EQUAL_INT8(0x88, A);
  TEST_ASSERT_EQUAL_INT8(0x55, YL);
}

void test_clr_longmem(void){
  uint16_t longmem = 0x1101;
  A = 0x22;
  MEM_WRITE_BYTE(longmem, 0x77);
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(2, exg_a_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x22, MEM_READ_BYTE(longmem));
  TEST_ASSERT_EQUAL_INT8(0x77, A);
}
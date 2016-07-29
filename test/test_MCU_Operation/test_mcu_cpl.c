#include "unity.h"
#include "MCU_Operation.h"
#include "ErrorObject.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


uint16_t addr;
void setUp(void){
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
  gpioInit(0x0, 0xFFFF);
  addr = 0x2233;
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}


/*

CPL ([$1234.w],X)

              M(M(longmem).w +X) ← FF - M(M(longmem).w+X)
                                              or
                                   M(M(longmem).w+X) XOR FF



*/


void test_mcu_cpl(void){
  MEM_WRITE_BYTE(addr,0x99);
  mcu_cpl(addr);
  
  TEST_ASSERT_EQUAL_INT8(0x66, MEM_READ_BYTE(addr));  // 0xFF - 0x99 = 0x66

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // C is always set to 1
}

void test_mcu_cpl_set_Z_flag(void){
  MEM_WRITE_BYTE(addr,0xFF);
  mcu_cpl(addr);
  
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(addr));  // 0xFF - 0xFF = 0

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(1, C);  // C is always set to 1
}

void test_mcu_cpl_set_N_flag(void){
  MEM_WRITE_BYTE(addr,0x0F);
  mcu_cpl(addr);
  
  TEST_ASSERT_EQUAL_INT8(0xF0, MEM_READ_BYTE(addr));  // 0xFF - 0x0F = 0xF0

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1 
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);  // C is always set to 1
}


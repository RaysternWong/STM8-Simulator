#include "unity.h"
#include "BCCM.h"
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

void test_all_the_bccm_function_given_C_is_0_should_remain_same_value(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0x55); // write 0x55 to memory
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  bccm_longmem_pos_0(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_1(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_2(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_3(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_4(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_5(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_6(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
  
  bccm_longmem_pos_7(instr);
  TEST_ASSERT_EQUAL_INT8(0x55, MEM_READ_BYTE(longmem) );
}


void test_bccm_longmem_pos_0_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x1, MEM_READ_BYTE(longmem) );
}


void test_bccm_longmem_pos_1_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_1(instr));
  TEST_ASSERT_EQUAL_INT8(0x2, MEM_READ_BYTE(longmem) );
}

void test_bccm_longmem_pos_2_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_2(instr));
  TEST_ASSERT_EQUAL_INT8(0x4, MEM_READ_BYTE(longmem) );
}


void test_bccm_longmem_pos_3_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_3(instr));
  TEST_ASSERT_EQUAL_INT8(0x8, MEM_READ_BYTE(longmem) );
}

void test_bccm_longmem_pos_4_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_4(instr));
  TEST_ASSERT_EQUAL_INT8(0x10, MEM_READ_BYTE(longmem) );
}

void test_bccm_longmem_pos_5_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_5(instr));
  TEST_ASSERT_EQUAL_INT8(0x20, MEM_READ_BYTE(longmem) );
}

void test_bccm_longmem_pos_6_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_6(instr));
  TEST_ASSERT_EQUAL_INT8(0x40, MEM_READ_BYTE(longmem) );
}

void test_bccm_longmem_pos_7_given_value_is_0_C_is_1(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bccm_longmem_pos_7(instr));
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(longmem) );
}

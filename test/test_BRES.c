#include "unity.h"
#include "BRES.h"
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



void test_bres_longmem_pos_0_given_value_is_0(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x1, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_0_given_value_is_also_1(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0x1);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x1, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_0_given_value_is_4(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0x4);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x5, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_1(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_1(instr));
  TEST_ASSERT_EQUAL_INT8(0x2, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_2(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_2(instr));
  TEST_ASSERT_EQUAL_INT8(0x4, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_3(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_3(instr));
  TEST_ASSERT_EQUAL_INT8(0x8, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_4(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_4(instr));
  TEST_ASSERT_EQUAL_INT8(0x10, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_5(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_5(instr));
  TEST_ASSERT_EQUAL_INT8(0x20, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_6(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_6(instr));
  TEST_ASSERT_EQUAL_INT8(0x40, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_7(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_7(instr));
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(longmem) );
}
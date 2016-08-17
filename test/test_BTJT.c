#include "unity.h"
#include "BTJT.h"
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

  pcToLoad = malloc(sizeof(uint32_t));
  *pcToLoad = 0;
  
  /*  result:
      If true (pos_N is 1)  pcToLoad = pcToLoad + 5 + 0x1101
                                     = 0x1106
                        
      If false (pos_N is 0)  pcToLoad = pcToLoad + 5 
                                      = 0x5
  */
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

//----------------------the bit is 0-------------------

void test_btjt_longmem_pos_0_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);  //bit0 is 0
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_1_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_1(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_2_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_2(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_3_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_3(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_4_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_4(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_5_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_5(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_6_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_6(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

void test_btjt_longmem_pos_7_given_the_bit_is_0(void){
  C = 1;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_7(instr));
  TEST_ASSERT_EQUAL_INT16(0x5, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(0, C);
}

//----------------------the bit is 1-------------------

void test_btjt_longmem_pos_0_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X1);  //bit1 is 1
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_1_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X2);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_1(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_2_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X4);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_2(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_3_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X8);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_3(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_4_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X10);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_4(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_5_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X20);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_5(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_6_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X40);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_6(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}

void test_btjt_longmem_pos_7_given_the_bit_is_1(void){
  C = 0;
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0X80);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(5, btjt_longmem_pos_7(instr));
  TEST_ASSERT_EQUAL_INT16(0x1106, *pcToLoad );
  TEST_ASSERT_EQUAL_INT8(1, C);
}
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

/*       1111 1111
    &    1111 1110
    --------------
         1111 1110
    ---------------
*/
void test_bres_longmem_pos_0_given_value_is_0xFF(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0xFE, MEM_READ_BYTE(longmem) );
}


/*       0000 0001
    &    1111 1110
    --------------
         0000 0000
    ---------------
*/
void test_bres_longmem_pos_0_given_value_is_1(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0x1);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(longmem) );
}

/*       1001 1011
    &    1111 1110
    --------------
         1001 1010
    ---------------
*/
void test_bres_longmem_pos_0_given_value_is_0X9B(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0x9B);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_0(instr));
  TEST_ASSERT_EQUAL_INT8(0x9A, MEM_READ_BYTE(longmem) );
}

/*       1111 1111
    &    1111 1101
    --------------
         1111 1101
    ---------------
*/
void test_bres_longmem_pos_1(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_1(instr));
  TEST_ASSERT_EQUAL_INT8(0xFD, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_2(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_2(instr));
  TEST_ASSERT_EQUAL_INT8(0xFB, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_3(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_3(instr));
  TEST_ASSERT_EQUAL_INT8(0xF7, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_4(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_4(instr));
  TEST_ASSERT_EQUAL_INT8(0xEF, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_5(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_5(instr));
  TEST_ASSERT_EQUAL_INT8(0xDF, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_6(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_6(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, MEM_READ_BYTE(longmem) );
}

void test_bres_longmem_pos_7(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xFF);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, bres_longmem_pos_7(instr));
  TEST_ASSERT_EQUAL_INT8(0x7F, MEM_READ_BYTE(longmem) );
}
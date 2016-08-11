#include "unity.h"
#include "RRCW.h"
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


/**    0x8765     1000  0111  0110  0101
                  bit 0 set to C, rotate right , then assign C to bit0

       0xC3B2     1100  0011  1011  0010

                  
       C = 1 , N  = 1;
*/

void test_rrcw_x(void){
  SET_X(0x8765);
  uint8_t instr[] = {0XAB};
  
  N = 0;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(1, rrcw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0xC3B2, X); 
  TEST_ASSERT_EQUAL_INT8(1, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

/**    0x4764     0100  0111  0110  0100
                  bit 0 set to C, rotate right , then assign C to bit0

       0x23B2     0010  0011  1011  0010

                  
       C = 0 , N = 0
*/

void test_rrcw_x_make_N_to_1(void){
  SET_X(0x4764);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  C = 1;
  
  TEST_ASSERT_EQUAL_INT8(1, rrcw_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x23B2, X); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_rrcw_y(void){
  SET_Y(0x0001);
  uint8_t instr[] = {0XAB};
  
  N = 0;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(2, rrcw_y(instr));
  TEST_ASSERT_EQUAL_INT16(0x8000, Y); 
  TEST_ASSERT_EQUAL_INT8(1, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}
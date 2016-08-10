#include "unity.h"
#include "SRAW.h"
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
                  bit 15 set to 1, shift right , but bit 15 fix

       0x83B2    0000  0011  1011  0010

                  
       C = 1 , N = 1
*/

void test_sraw_x(void){
  SET_X(0x8765);
  uint8_t instr[] = {0XAB};
  
  N = 0;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(1, sraw_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x83B2, X); 
  TEST_ASSERT_EQUAL_INT8(1, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}



void test_sraw_x_make_N_to_1(void){
  SET_X(0x1);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 0;
  C = 1;
  
  TEST_ASSERT_EQUAL_INT8(1, sraw_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x0, X); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(1, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

/**    0x0765     0000  0111  0110  0101
                  bit 15 set to 1, shift right , but bit 15 fix

       0x03B2    0000  0011  1011  0010

                  
       C = 1 , N = 0
*/

void test_sraw_y(void){
  SET_Y(0x0765);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(2, sraw_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x03B2, Y); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

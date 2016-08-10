#include "unity.h"
#include "SLLW.h"
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
                  bit 15 set to 1, shift left 

       0x0ECA      0000  1110  1100  1010

                  
       C = 1
*/

void test_sllw_x(void){
  SET_X(0x8765);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(1, sllw_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x0ECA, X); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

/**    0xC765     1100  0111  0110  0101
                  bit 15 set to 1, shift left 

       0x8ECA    1000  1110  1100  1010

                  
       C = 1 , N = 1
*/

void test_sllw_x_make_N_to_1(void){
  SET_X(0xC765);
  uint8_t instr[] = {0XAB};
  
  N = 0;
  Z = 1;
  C = 0;
  
  TEST_ASSERT_EQUAL_INT8(1, sllw_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x8ECA, X); 
  TEST_ASSERT_EQUAL_INT8(1, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

/**    0x0765     0000  0111  0110  0101
                  bit 15 set to 1, shift left 

       0x0ECA     0000  1110  1100  1010

                  
       C = 0
*/

void test_sllw_y(void){
  SET_Y(0x0765);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  C = 1;
  
  TEST_ASSERT_EQUAL_INT8(2, sllw_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x0ECA, Y); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}
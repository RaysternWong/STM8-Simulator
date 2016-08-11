#include "unity.h"
#include "RLWA.h"
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


/**    0x8765    
                  
       XH = 0x87 , Xl = 0x65
     
       A = XH;
       XH = XL;
       XL = A;
                  
      X = 0x6587,  A = 0x87
*/

void test_rlwa_x(void){
  SET_X(0x8765);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  A = 0;
  
  TEST_ASSERT_EQUAL_INT8(1, rlwa_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x6587, X); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0x87, A); 
}

void test_rlwa_x_make_N_to_1(void){
  SET_X(0x6688);
  uint8_t instr[] = {0XAB};
  
  N = 0;
  Z = 1;

  TEST_ASSERT_EQUAL_INT8(1, rlwa_x(instr));
  TEST_ASSERT_EQUAL_INT16(0x8866, X); 
  TEST_ASSERT_EQUAL_INT8(1, N);  // bit 15 is 1
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0x66, A);
}

void test_rlwa_x_make_Z_to_1(void){
  SET_X(0x0);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 0;

  TEST_ASSERT_EQUAL_INT8(1, rlwa_x(instr));
  TEST_ASSERT_EQUAL_INT16(0, X); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(1, Z); 
  TEST_ASSERT_EQUAL_INT8(0x0, A);
}


void test_rlwa_y(void){
  SET_Y(0x8765);
  uint8_t instr[] = {0XAB};
  
  N = 1;
  Z = 1;
  
  TEST_ASSERT_EQUAL_INT8(2, rlwa_y(instr));
  TEST_ASSERT_EQUAL_INT16(0x6587, Y); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0x87, A);
}
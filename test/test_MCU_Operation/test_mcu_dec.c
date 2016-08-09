#include "unity.h"
#include "MCU_Operation.h"
#include "ErrorObject.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


void setUp(void){
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
 
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/**

  INC ([$1234.w],X)
                      M(M(longmem).w + X) ← M(M(longmem).w + X) + 1
               
*/

void test_mcu_dec_set_negative_flag(void){

  MEM_WRITE_BYTE(0x1133 ,0x81);
  mcu_dec(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);  
}


void test_mcu_dec_set_Z_flag(void){

  MEM_WRITE_BYTE(0x1133,1);
  mcu_dec(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);   
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

/** 
*
*   Overflow occurs if 
*    (-A) - (+B) = +C
*
*/
void test_mcu_dec_set_V_flag(void){

  MEM_WRITE_BYTE(0x1133,0x80);
  mcu_dec(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0x7F, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(1, V); // 0x80(+value) + 0x1(+value) = 0x7F(-value)
  TEST_ASSERT_EQUAL(0, I1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, I0);
  TEST_ASSERT_EQUAL(0, N);  
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

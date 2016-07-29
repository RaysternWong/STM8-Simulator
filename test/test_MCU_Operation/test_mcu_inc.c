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

void test_mcu_inc_set_incative_flag_carry_flag(void){

  MEM_WRITE_BYTE(0x1133 ,0x81);
  mcu_inc(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0x82, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);  // bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);  
}


void test_mcu_inc_set_Z_flag(void){

  MEM_WRITE_BYTE(0x1133,-1);
  mcu_inc(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);   
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

/** overflow occur when sum of 2 positive number and get negative number,
           
*/
void test_mcu_inc_set_V_flag(void){

  MEM_WRITE_BYTE(0x1133,0x7F);
  mcu_inc(0x1133);
  
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(0x1133));

  TEST_ASSERT_EQUAL(1, V); // 0x7F(+value) + 0x1(+value) = 0x80(-value)
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(1, N);   // bit 7 is 1 
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);  
}

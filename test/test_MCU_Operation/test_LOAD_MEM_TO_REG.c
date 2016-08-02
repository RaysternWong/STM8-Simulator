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


/*

    LD A,($12,SP)     | A ← M(SP+shortoff)

    LD ($12,SP),A     |M(SP+shortoff) ← A

    LD A, XH          |A ← XH

*/


void test_LOAD_MEM_TO_REG_given_load_0xBB_to_A(void){
  

  uint32_t value1 = 0xBB;
  
  // LOAD_MEM_TO_REG(A, value);
  // TEST_ASSERT_EQUAL_INT8(0xBB, A);
  // TEST_ASSERT_EQUAL_INT8(0, Z);
  // TEST_ASSERT_EQUAL_INT8(1, N); // bit 7 is 1
}

void xtest_LOAD_MEM_TO_REG_given_load_A_to_address(void){
  
  // uint16_t addr = 0x7788;
  // MEM_WRITE_BYTE(addr, 0x33);
  // A = 0;
  
  // LOAD_BYTE( MEM_READ_BYTE(addr), A);
  // TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(addr));
  // TEST_ASSERT_EQUAL_INT8(1, Z); // value is 0
  // TEST_ASSERT_EQUAL_INT8(0, N); 
}
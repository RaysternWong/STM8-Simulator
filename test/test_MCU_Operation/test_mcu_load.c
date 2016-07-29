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

CPL ([$1234.w],X)

              M(M(longmem).w +X) ← FF - M(M(longmem).w+X)
                                              or
                                   M(M(longmem).w+X) XOR FF



*/


void test_mcu_load_given_load_byte_from_src_to_A(void){
  A = 0x88;
  
}

#include "unity.h"
#include "BREAK.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "CException.h"
#include <malloc.h>


void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_instr_break(void){
  CEXCEPTION_T err;
  uint8_t instr[] = {0XAB};
  
  Try{
    
  TEST_ASSERT_EQUAL_INT8(1, instr_break(instr));
  TEST_FAIL_MESSAGE("Expected ERR_BREAK");
    

  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_BREAK, err, "Expected ERR_BREAK");
  }
}
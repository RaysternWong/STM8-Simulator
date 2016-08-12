#include "unity.h"
#include "WFE.h"
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

void test_wfe(void){
  CEXCEPTION_T err;
  uint8_t instr[] = {0XAB};
  
  Try{
    
  TEST_ASSERT_EQUAL_INT8(1, wfe(instr));
  TEST_FAIL_MESSAGE("Expected ERR_WFE");
    

  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_WFE, err, "Expected ERR_WFE");
  }
}
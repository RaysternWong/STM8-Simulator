#include "unity.h"
#include "TRAP.h"
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
 
  pcToLoad = malloc(sizeof(uint32_t));

}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
  free(pcToLoad);
}


/**

Syntax TRAP
            Operation PC = PC + 1
            (SP--) = LSB (PC)
            (SP--) = MSB (PC)
            (SP--) = Ext(PC)
            (SP--) = YL
            (SP--) = YH
            (SP--) = XL
            (SP--) = XH
            (SP--) = A
            (SP--) = CC
            
          PC = TRAP Interrupt Vector Contents
*/


void test_trap(void){
  I0 = 0;
  I0 = 0;
  *pcToLoad = 0x012244; //*pcToLoad + 1 = 0x012245
  
//pcl =0x45
//pch =0x22
//pce =0x01 
  YL = 0XE4;
  YH = 0XD6;
  XL = 0XC9;
  XH = 0X68;
  A  = 0XBB;
  CC = 0X55;
  
	uint8_t instr[] = {0XBB};

  TEST_ASSERT_EQUAL_INT8(1, trap(instr));
  TEST_ASSERT_EQUAL_INT16(0x012245, *pcToLoad);
  TEST_ASSERT_EQUAL_INT8(0X55, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0XBB, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0X68, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0XC9, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0XD6, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0XE4, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0X01, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0X22, mcu_pop());
  TEST_ASSERT_EQUAL_INT8(0X45, mcu_pop());
  
  TEST_ASSERT_EQUAL_INT8(1, I0);
  TEST_ASSERT_EQUAL_INT8(1, I1);
}

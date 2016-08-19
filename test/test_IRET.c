#include "unity.h"
#include "IRET.h"
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

Syntax IRET
                Operation CC = (++SP)
                A   = (++SP)
                XH  = (++SP)
                XL  = (++SP)
                YH  = (++SP)
                YL  = (++SP)
                PCE = (++SP)
                PCH = (++SP)
                PCL = (++SP)
*/


void test_trap(void){
  I0 = 0;
  I0 = 0;

  // 0X01B2A1 will be assign to *pcToLoad
  mcu_push(0xA1); // For PCL  
  mcu_push(0XB2); // For PCH
  mcu_push(0X01); // For PCE
  
  mcu_push(0X88); // For YL
  mcu_push(0X99); // For YH
  
  mcu_push(0X66); // For XL
  mcu_push(0X77); // For XH
  
  mcu_push(0X11); // For A
  mcu_push(0X7A); // For CC
  

 
	uint8_t instr[] = {0XBB};

  TEST_ASSERT_EQUAL_INT8(1, iret(instr));
 
  TEST_ASSERT_EQUAL_INT8(0X7A, CC);
  TEST_ASSERT_EQUAL_INT8(0X11, A);
  TEST_ASSERT_EQUAL_INT8(0X77, XH);
  TEST_ASSERT_EQUAL_INT8(0X66, XL);
  TEST_ASSERT_EQUAL_INT8(0X99, YH);
  TEST_ASSERT_EQUAL_INT8(0X88, YL);
  TEST_ASSERT_EQUAL_INT16(0X01B2A1, *pcToLoad);
  
  
  //where 0x7A will assigned to condition flag (CC), and CC is union structure to each flag
  //          C  Z  N  IO H  I1 V
  //0X7A : 0  1  1  1  1  0  1  0 
  TEST_ASSERT_EQUAL_INT8(0, V);
  TEST_ASSERT_EQUAL_INT8(1, I1);
  TEST_ASSERT_EQUAL_INT8(0, H);
  TEST_ASSERT_EQUAL_INT8(1, I0);
  TEST_ASSERT_EQUAL_INT8(1, N);
  TEST_ASSERT_EQUAL_INT8(1, Z);
  TEST_ASSERT_EQUAL_INT8(1, C);
}
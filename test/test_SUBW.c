#include "unity.h"
#include "SUBW.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>
#include "ErrorObject.h"
#include "Description.h"


uint16_t value;
void setUp(void)
{
  instantiateCPU();
  ramBlock = createMemoryBlock(0, 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  SET_X(0x8888);
  SET_Y(0x8888);
  value = 0x22;
  // result = 0x8888 - 0x2222 = 0x8866
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}

void xtest_subw_x_word(void){ 
  uint8_t instr[] = {0XAB, 0X22, 0X22};
  
  TEST_ASSERT_EQUAL(3, subw_x_word(instr));
  TEST_ASSERT_EQUAL_INT16(0x6666, X);
}

void test_subw_x_longmem(void){
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  value);
  TEST_ASSERT_EQUAL(4, subw_x_longmem(instr));
  TEST_ASSERT_EQUAL_INT16(0x8866, X);
}


void test_subw_x_shortoff_sp(void){
  SPH = 0X2B;
  SPL = 0X11;
  
  uint8_t addr = 0x11;
  uint8_t instr[] = {0XBB, addr};
  
  MEM_WRITE_BYTE( 0x2B22,  value);  //2B11 + 11 = 2B22
  
  TEST_ASSERT_EQUAL(3, subw_x_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT16(0x8866, X);
}


void test_subw_y_word(void){
  uint8_t instr[] = {0XAB, 0X22, 0X22};
  
  TEST_ASSERT_EQUAL(4, subw_y_word(instr));
  TEST_ASSERT_EQUAL_INT16(0x6666, Y);
}

void test_subw_y_longmem(void){
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  
  MEM_WRITE_BYTE( 0x1101,  value);
  
  TEST_ASSERT_EQUAL(4, subw_y_longmem(instr));
  TEST_ASSERT_EQUAL_INT16(0x8866, Y);
}


void test_subw_y_shortoff_sp(void){  
  SPH = 0X2B;
  SPL = 0X11;
  
  uint8_t addr = 0x11; 
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( 0x2B22,  value);  //2B11 + 11 = 2B22
  

  TEST_ASSERT_EQUAL(3, subw_y_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT16(0x8866, Y);
}

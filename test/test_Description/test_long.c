#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>


uint8_t value, msbMem, lsbMem;
uint16_t longMem;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to 0x027FFF, for testing purpose  
  ramBlock = createMemoryBlock(0x0000 , 0x027FFF);
  setMemoryTable( ramMemory , 0 , 0x027FFF); 
  
  msbMem = 0x33;
  lsbMem = 0x44;
  longMem = 0x3344;

  
  value = 0x22;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

////-------------------------------------destination marco testing--------------------------------------------

void test_GET_LONG_MEM(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  TEST_ASSERT_EQUAL_INT16(longMem, GET_LONG_MEM(instr));
}

void test_GET_LONG_OFF_X(void){ 
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
 
  TEST_ASSERT_EQUAL_INT16( X+longMem, GET_LONG_OFF_X(instr));
}

void test_GET_LONG_OFF_Y(void){
  SET_Y(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
 
  TEST_ASSERT_EQUAL_INT16( Y+longMem, GET_LONG_OFF_Y(instr));
}

void test_GET_LONG_PTR_W(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  
  TEST_ASSERT_EQUAL_INT16( 0xccee, GET_LONG_PTR_W(instr));
}

void test_GET_LONG_PTR_E(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  
  TEST_ASSERT_EQUAL_INT32( 0x01eeaa, GET_LONG_PTR_E(instr));
}

void test_GET_LONG_PTR_W_X(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  
  TEST_ASSERT_EQUAL_INT16( X + 0xccee, GET_LONG_PTR_W_X(instr));
}

void test_GET_LONG_PTR_W_Y(void){
  SET_Y(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  
  TEST_ASSERT_EQUAL_INT16( Y + 0xccee, GET_LONG_PTR_W_Y(instr));
}
//-------------------------------------src marco testing--------------------------------------------

void test_GET_LONG_MEM_SRC(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  MEM_WRITE_BYTE( longMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, GET_LONG_MEM_SRC(instr));
}

void test_GET_LONG_OFF_X_SRC(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t xPlusLongMem = X + longMem;
  MEM_WRITE_BYTE( xPlusLongMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, GET_LONG_OFF_X_SRC(instr));
}

void test_GET_LONG_OFF_Y_SRC(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t yPlusLongMem = Y + longMem;
  MEM_WRITE_BYTE( yPlusLongMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, GET_LONG_OFF_Y_SRC(instr));
}

void test_GET_LONG_PTR_W_SRC(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( 0xccee ,  value); 
  
  TEST_ASSERT_EQUAL_INT8( value, GET_LONG_PTR_W_SRC(instr));
}

void test_GET_LONG_PTR_E_SRC(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  MEM_WRITE_BYTE( 0x01eeaa ,  value); 
   
  TEST_ASSERT_EQUAL_INT8( value, GET_LONG_PTR_E_SRC(instr));
}

void test_GET_LONG_PTR_W_X_SRC(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};

  uint16_t longMem1 = longMem + 1;
  uint16_t xPlusLongPtr = X + 0xccee;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( xPlusLongPtr , value); 

  TEST_ASSERT_EQUAL_INT8( value, GET_LONG_PTR_W_X_SRC(instr));
}

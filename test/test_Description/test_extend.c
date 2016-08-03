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

//-------------------------------------dst marco testing--------------------------------------------

void test_GET_EXT_MEM(void){
  uint8_t instr[] = { 0xAB, 0x11,0x22,0x33};
  uint8_t *opcode = instr;
  
  TEST_ASSERT_EQUAL_INT32(0X112233, GET_EXT_MEM(opcode) );
}

void test_GET_EXT_OFF_X(void){
  SET_X(0x11);
  uint8_t instr[] = { 0xAB, 0x11,0x22,0x33};
  uint8_t *opcode = instr;
  
  TEST_ASSERT_EQUAL_INT32(0X112244, GET_EXT_OFF_X(opcode) ); // 0X112233 + 0x11
}

void test_GET_EXT_OFF_Y(void){
  SET_Y(0x11);
  uint8_t instr[] = { 0xAB, 0x11,0x22,0x33};
  uint8_t *opcode = instr;
  
  TEST_ASSERT_EQUAL_INT32(0X112244, GET_EXT_OFF_Y(opcode) ); // 0X112233 + 0x11
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

void test_GET_LONG_PTR_E_X(void){
  SET_X(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  
  TEST_ASSERT_EQUAL_INT32( 0x01eebb, GET_LONG_PTR_E_X(instr));  // 0x01eeaa + 0x11
}

void test_GET_LONG_PTR_E_Y(void){
  SET_Y(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  
  TEST_ASSERT_EQUAL_INT32( 0x01eebb, GET_LONG_PTR_E_Y(instr));  // 0x01eeaa + 0x11
}

//-------------------------------------src marco testing--------------------------------------------

void test_GET_EXT_MEM_SRC(void){
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};

  MEM_WRITE_BYTE( 0x012233 ,  value); 
   
  TEST_ASSERT_EQUAL_INT8( value, GET_EXT_MEM_SRC(instr));
}

void test_GET_EXT_OFF_X_SRC(void){
  SET_X(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  MEM_WRITE_BYTE( 0X012244 ,  value);   // 0X012233 + 0x11 = 0X012244
  
  TEST_ASSERT_EQUAL_INT8( value, GET_EXT_OFF_X_SRC(instr)); 
}

void test_GET_EXT_OFF_Y_SRC(void){
  SET_Y(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  MEM_WRITE_BYTE( 0X012244 ,  value);   // 0X012233 + 0x11 = 0X012244
  
  TEST_ASSERT_EQUAL_INT8( value, GET_EXT_OFF_Y_SRC(instr)); 
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

void test_GET_LONG_PTR_E_X_SRC(void){
  SET_X(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  MEM_WRITE_BYTE( 0x01eebb ,  value); 
  
  TEST_ASSERT_EQUAL_INT8( value, GET_LONG_PTR_E_X_SRC(instr));  
}

void test_GET_LONG_PTR_E_Y_SRC(void){
  SET_Y(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0x01);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  MEM_WRITE_BYTE( 0x01eebb ,  value); 
  
  TEST_ASSERT_EQUAL_INT8( value, GET_LONG_PTR_E_Y_SRC(instr));  
}
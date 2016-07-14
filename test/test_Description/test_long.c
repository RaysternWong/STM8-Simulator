#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>


uint8_t value, msbMem, lsbMem;
uint16_t longMem;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
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

void test_GET_LONG_MEM(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
 
  TEST_ASSERT_EQUAL_INT16(longMem, GET_LONG_MEM(opcode));
}

void test_GET_LONG_OFF_X(void){
  
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
 
  TEST_ASSERT_EQUAL_INT16( X+longMem, GET_LONG_OFF_X(opcode));
}

void test_GET_LONG_OFF_Y(void){
  
  SET_Y(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
 
  TEST_ASSERT_EQUAL_INT16( Y+longMem, GET_LONG_OFF_Y(opcode));
}

void test_GET_LONG_PTR_W(void){

  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  
  TEST_ASSERT_EQUAL_INT16( 0xccee, GET_LONG_PTR_W(opcode));
}

void test_GET_LONG_PTR_E(void){

  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( longMem2  ,  0xaa);
  
  TEST_ASSERT_EQUAL_INT32( 0xcceeaa, GET_LONG_PTR_E(opcode));
}

void test_GET_LONG_PTR_W_X(void){
  
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  
  TEST_ASSERT_EQUAL_INT16( X + 0xccee, GET_LONG_PTR_W_X(opcode));
}


void test_getLongMemSrc(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  MEM_WRITE_BYTE( longMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, getLongMemSrc(instr));
}

void test_getLongOffXSrc(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t xPlusLongMem = X + longMem;
  MEM_WRITE_BYTE( xPlusLongMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, getLongOffXSrc(instr));
}

void test_getLongOffYSrc(void){
  SET_X(0x2B11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t yPlusLongMem = Y + longMem;
  MEM_WRITE_BYTE( yPlusLongMem ,  value); 
  
  TEST_ASSERT_EQUAL_INT8(value, getLongOffYSrc(instr));
}

void test_getLongPtrWSrc(void){

  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
  uint16_t longMem1 = longMem + 1;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( 0xccee ,  value); 
  
  TEST_ASSERT_EQUAL_INT8( value, getLongPtrWSrc(opcode));
}

void test_getLongPtrWXSrc(void){

  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint8_t *opcode = instr;
  uint16_t longMem1 = longMem + 1;
  uint16_t xPlusLongPtr = X + 0xccee;
  
  MEM_WRITE_BYTE( longMem   ,  0xcc);
  MEM_WRITE_BYTE( longMem1  ,  0xee);
  MEM_WRITE_BYTE( xPlusLongPtr , value); 
  
  TEST_ASSERT_EQUAL_INT8( value, getLongPtrWXSrc(opcode));
}

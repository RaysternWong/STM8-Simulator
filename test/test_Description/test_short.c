#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>


uint8_t value;
void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  value = 0x22;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_GET_NEXT_BYTE_OF(void){

  uint8_t shortMem = 0xAD;

  uint8_t instr[] = {0XBB, shortMem};
  uint8_t *opcode = instr;
 
  TEST_ASSERT_EQUAL_INT8(shortMem, GET_NEXT_BYTE_OF(opcode));
}

void test_getShortMemSrc(void){
  uint8_t shortMem = 0xAD;
  MEM_WRITE_BYTE(shortMem ,value);
  
  uint8_t instr[]  = {0XBB, shortMem};
  uint8_t *opcode = instr;
  
  TEST_ASSERT_EQUAL_INT8(value, GET_SHORT_MEM_SRC( opcode));
}

void test_GET_SHORT_OFF_X(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  uint8_t *opcode = instr;
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT16(0X2B22, GET_SHORT_OFF_X(opcode));
}

void test_GET_SHORT_OFF_Y(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  uint8_t *opcode = instr;
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT16(0X2B22, GET_SHORT_OFF_Y(opcode));
}

void test_GET_SHORT_OFF_SP(void){

  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  uint8_t *opcode = instr;
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT16(0X2B22, GET_SHORT_OFF_SP(opcode));
}

void test_getShortOffXSrc(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffXSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortOffYSrc(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffYSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortOffSPSrc(void){

  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffSPSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_GET_SHORT_PTR_W(void){

  uint8_t instr[] = {0XFB, 0X11};
  uint8_t *opcode = instr;  
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  uint16_t word = GET_SHORT_PTR_W(opcode);
  TEST_ASSERT_EQUAL_INT16(0xAABB, word); 
}

void test_getShortPtrWSrc(void){

  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xAABB ,  value);  
  
  uint8_t src = getShortPtrWSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}

void test_GET_SHORT_PTR_W_X(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  uint8_t *opcode = instr;
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  //2b11 + aabb = d5cc
  TEST_ASSERT_EQUAL_INT16(0xd5cc, GET_SHORT_PTR_W_X(opcode)); 
}

void test_GET_SHORT_PTR_W_Y(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  uint8_t *opcode = instr;
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  //2b11 + aabb = d5cc
  TEST_ASSERT_EQUAL_INT16(0xd5cc, GET_SHORT_PTR_W_Y(opcode)); 
}

void test_getShortPtrWXSrc(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xd5cc ,  value);  //2b11 + aabb = d5cc
  
  uint8_t src = getShortPtrWXSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}

void test_getShortPtrWYSrc(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xd5cc ,  value);  //2b11 + aabb = d5cc
  
  uint8_t src = getShortPtrWYSrc(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}
#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
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


void test_getShortmemSrc(void){

  uint8_t shortMem = 0xAD;
  MEM_WRITE_BYTE(shortMem ,value);
  
  uint8_t instr[]  = {0XBB, shortMem};
  
  uint8_t src = getShortmemSrc( instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortOffX(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffX( instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortOffSP(void){

  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffSP( instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortOffY(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  uint8_t src = getShortOffY( instr);
  TEST_ASSERT_EQUAL_INT8(value, src);
}

void test_getShortW(void){

  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  uint16_t word = getShortW( instr);
  TEST_ASSERT_EQUAL_INT16(0xAABB, word); 
}

void test_getShortPtrW(void){

  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xAABB ,  value);  
  
  uint8_t src = getShortPtrW(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}

void test_getShortPtrX(void){

  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xd5cc ,  value);  //2b11 + aabb = d5cc
  
  uint8_t src = getShortPtrX(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}

void test_getShortPtrY(void){

  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11}; 
  
  MEM_WRITE_BYTE( 0x11 ,  0xAA);  
  MEM_WRITE_BYTE( 0x12 ,  0xBB);  
  
  MEM_WRITE_BYTE( 0xd5cc ,  value);  //2b11 + aabb = d5cc
  
  uint8_t src = getShortPtrY(instr);
  TEST_ASSERT_EQUAL_INT8(value, src); 
}
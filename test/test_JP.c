#include "unity.h"
#include "JP.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

/**

JP ([$1234.w],X) PC ← M(longmem).w + X

*/



void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  pcToLoad = malloc(sizeof(uint32_t));
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
  free(pcToLoad);
}

void test_jp_longmem(void){ 
  uint8_t instr[] = {0XAB, 0x33, 0x77}; 
 
  TEST_ASSERT_EQUAL_INT8( 3, jp_longmem(instr) );  
  TEST_ASSERT_EQUAL_INT16( 0x3377 , *pcToLoad );   
}

void test_jp_x(void){
  uint8_t instr[] = {0XAB};
  SET_X(0xdd33);

  TEST_ASSERT_EQUAL_INT8( 1, jp_x(instr) ); 
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , *pcToLoad );   
}

void test_jp_shortoff_x(void){
  uint8_t instr[] = {0XFB, 0x22};
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 2, jp_shortoff_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x22 , *pcToLoad );   
}

void test_jp_longoff_x(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x55};
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, jp_longoff_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x2255 , *pcToLoad );  
}

void test_jp_y(void){
  uint8_t instr[] = {0XAB};
  SET_Y(0xdd33);

  TEST_ASSERT_EQUAL_INT8( 2, jp_y(instr) ); 
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , *pcToLoad ); 
}
  
void test_jp_shortoff_y(void){
  uint8_t instr[] = {0XFB, 0x22};
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, jp_shortoff_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x22 , *pcToLoad );   
}

void test_jp_longoff_y(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x55};
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 4, jp_longoff_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x2255 , *pcToLoad );  
}

void test_jp_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  
  TEST_ASSERT_EQUAL_INT8( 3, jp_shortptr_w(instr) );
  TEST_ASSERT_EQUAL_INT16( 0x6699, *pcToLoad ); 
}
  
void test_jp_longptr_w(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x77};
  MEM_WRITE_BYTE( 0x2277, 0x66);
  MEM_WRITE_BYTE( 0x2278, 0x99);
  
  TEST_ASSERT_EQUAL_INT8( 4, jp_longptr_w(instr) );
  TEST_ASSERT_EQUAL_INT16( 0x6699, *pcToLoad ); 
}

void test_jp_shortptr_w_x(void){ 
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, jp_shortptr_w_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x6699, *pcToLoad ); 
}

void test_jp_longptr_w_x(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x77};
  MEM_WRITE_BYTE( 0x2277, 0x66);
  MEM_WRITE_BYTE( 0x2278, 0x99);
  SET_X(0x2B11);
    
  TEST_ASSERT_EQUAL_INT8( 4, jp_longptr_w_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x6699, *pcToLoad ); 
}

void test_jp_shortptr_w_y(void){ 
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, jp_shortptr_w_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x6699, *pcToLoad ); 
}
#include "unity.h"
#include "CALL.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

//Please refer all the definations and marco in MCU_Operation.h

/**
                  PC← PC + 4
                  M(SP--) ← PCL
CALL [$1234.w]    M(SP--) ← PCH
                  PCH← M(longmem)
                  PCL← M(longmem + 1)
                  
  The PC wont change while execute this instruction,
  but store the value into pcToLoad,
  then only assign the value from pcToLoad to PC in executeOneInstructon()
*/

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  pcToLoad = malloc(sizeof(uint32_t));
  *pcToLoad = 0;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
  free(pcToLoad);  
}

void test_call_longmem(void){ 
  uint8_t instr[] = {0XAB, 0x33, 0x77}; 
 
  TEST_ASSERT_EQUAL_INT8( 3, call_longmem(instr) );  
  TEST_ASSERT_EQUAL_INT16( 0x3377 , *pcToLoad );   
}

void test_call_x(void){
  uint8_t instr[] = {0XAB};
  SET_X(0xdd33);

  TEST_ASSERT_EQUAL_INT8( 1, call_x(instr) ); 
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , *pcToLoad );   
}

void test_call_shortoff_x(void){
  uint8_t instr[] = {0XFB, 0x22};
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 2, call_shortoff_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x22 , *pcToLoad );   
}

void test_call_longoff_x(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x55};
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, call_longoff_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x2255 , *pcToLoad );  
}

void test_call_y(void){
  uint8_t instr[] = {0XAB};
  SET_Y(0xdd33);

  TEST_ASSERT_EQUAL_INT8( 2, call_y(instr) ); 
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , *pcToLoad ); 
}
  
void test_call_shortoff_y(void){
  uint8_t instr[] = {0XFB, 0x22};
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, call_shortoff_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x22 , *pcToLoad );   
}

void test_call_longoff_y(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x55};
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 4, call_longoff_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x2255 , *pcToLoad );  
}

void test_call_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  
  TEST_ASSERT_EQUAL_INT8( 3, call_shortptr_w(instr) );
  TEST_ASSERT_EQUAL_INT16( 0x6699, *pcToLoad ); 
}
  
void test_call_longptr_w(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x77};
  MEM_WRITE_BYTE( 0x2277, 0x66);
  MEM_WRITE_BYTE( 0x2278, 0x99);
  
  TEST_ASSERT_EQUAL_INT8( 4, call_longptr_w(instr) );
  TEST_ASSERT_EQUAL_INT16( 0x6699, *pcToLoad ); 
}

void test_call_shortptr_w_x(void){ 
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  SET_X(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, call_shortptr_w_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x6699, *pcToLoad ); 
}

void test_call_longptr_w_x(void){ 
  uint8_t instr[] = {0XFB, 0x22, 0x77};
  MEM_WRITE_BYTE( 0x2277, 0x66);
  MEM_WRITE_BYTE( 0x2278, 0x99);
  SET_X(0x2B11);
    
  TEST_ASSERT_EQUAL_INT8( 4, call_longptr_w_x(instr) );
  TEST_ASSERT_EQUAL_INT16( X + 0x6699, *pcToLoad ); 
}

void test_call_shortptr_w_y(void){ 
  uint8_t instr[] = {0XFB, 0x22};
  MEM_WRITE_BYTE( 0x22, 0x66);
  MEM_WRITE_BYTE( 0x23, 0x99);
  SET_Y(0x2B11);
  
  TEST_ASSERT_EQUAL_INT8( 3, call_shortptr_w_y(instr) );
  TEST_ASSERT_EQUAL_INT16( Y + 0x6699, *pcToLoad ); 
}
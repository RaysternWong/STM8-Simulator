#include "unity.h"
#include "CALL.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

//Please refer all the definations and marco in MCU_Operation.h

/**
                  PC← PC + 4
                  M(SP--) ← PCL
CALL [$1234.w]    M(SP--) ← PCH
                  PCH← M(longmem)
                  PCL← M(longmem + 1)
*/

uint8_t value;
uint8_t offSet1, offSet2;
uint8_t ptr1, ptr2;
uint16_t fullOffSet, fullPtr;
uint16_t inputSP, sp_minus1, sp_minus2;

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  offSet1 = 0x2d;
  offSet2 = 0x3b;
  fullOffSet = 0x2d3b;
  
  ptr1 = 0x1b;
  ptr2 = 0x88;
  fullPtr = 0x1b88;
  
 
  inputSP = 0x1122;
  sp_minus1 = inputSP - 1;
  sp_minus2 = inputSP - 2;
  SET_SP(inputSP);
  
  PCH = 0x33;
  PCL = 0x44;
  
  value = 0xEE;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_call_longmem(void){
 
  uint8_t memMSB = 0xAA, memLSB = 0xBB;
  uint16_t longmem = 0xAABB;
  MEM_WRITE_BYTE(longmem, value);
  
  uint8_t instr[] = {0XAB, memMSB, memLSB}; 
  
  uint8_t length = call_longmem(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_x(void){
  
  SET_X(0xdd33);
  uint8_t instr[] = {0XAB}; 
  
  uint8_t length = call_x(instr);
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 1, length );  
}

void test_call_y(void){
  
  SET_Y(0xdd33);
  uint8_t instr[] = {0XAB}; 
  
  uint8_t length = call_y(instr);
  TEST_ASSERT_EQUAL_INT16( 0xdd33 , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 2, length );  
}

void test_call_shortoff_x(void){
  
  SET_X(0x2B11);
  uint16_t shortOffX = 0x2B11 + offSet1;
  MEM_WRITE_BYTE( shortOffX, value);  
  
  uint8_t instr[] = {0XFB, offSet1};
  
  uint8_t length = call_shortoff_x(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 2, length );  
}

void test_call_shortoff_y(void){
  
  SET_Y(0x2B11);
  uint16_t shortOffY = 0x2B11 + offSet1;
  MEM_WRITE_BYTE( shortOffY, value);  
  
  uint8_t instr[] = {0XFB, offSet1};
  
  uint8_t length = call_shortoff_y(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_longoff_x(void){
  SET_X(0x2B11);
  uint16_t longOffX = 0x2B11 + fullOffSet;
  MEM_WRITE_BYTE( longOffX , value);  

  uint8_t instr[] = {0XFB, offSet1, offSet2};
  
  uint8_t length = call_longoff_x(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_longoff_y(void){
  SET_Y(0x2B11);
  uint16_t longOffY = 0x2B11 + fullOffSet;
  MEM_WRITE_BYTE( longOffY , value);  

  uint8_t instr[] = {0XFB, offSet1, offSet2};
  
  uint8_t length = call_longoff_y(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 4, length );  
}

void test_call_shortptr(void){
  MEM_WRITE_BYTE(  offSet1    , ptr1);  
  MEM_WRITE_BYTE( (offSet1+1) , ptr2);  
  MEM_WRITE_BYTE( fullPtr     , value);  

  uint8_t instr[] = {0XFB, offSet1};
  
  uint8_t length = call_shortptr(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_longptr(void){
  MEM_WRITE_BYTE( fullOffSet     , ptr1);  
  MEM_WRITE_BYTE( (fullOffSet+1) , ptr2);  
  MEM_WRITE_BYTE( fullPtr        , value);  

  uint8_t instr[] = {0XFB, offSet1, offSet2};
  
  uint8_t length = call_longptr(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 4, length );  
}

void test_call_shortptr_x(void){
  SET_X(0x2B11);
  MEM_WRITE_BYTE(  offSet1     , ptr1);  
  MEM_WRITE_BYTE( (offSet1+1)  , ptr2);  
  MEM_WRITE_BYTE( (fullPtr + X), value);  

  uint8_t instr[] = {0XFB, offSet1};
  
  uint8_t length = call_shortptr_x(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_shortptr_y(void){
  SET_Y(0x2B11);
  MEM_WRITE_BYTE(  offSet1     , ptr1);  
  MEM_WRITE_BYTE( (offSet1+1)  , ptr2);  
  MEM_WRITE_BYTE( (fullPtr + Y), value);  

  uint8_t instr[] = {0XFB, offSet1};
  
  uint8_t length = call_shortptr_y(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}

void test_call_longptr_x(void){
  SET_Y(0x2B11);
  MEM_WRITE_BYTE(  fullOffSet     , ptr1);  
  MEM_WRITE_BYTE( (fullOffSet+1)  , ptr2);  
  MEM_WRITE_BYTE( (fullPtr + X), value);  

  uint8_t instr[] = {0XFB, offSet1, offSet2};
  
  uint8_t length = call_longptr_x(instr);
  TEST_ASSERT_EQUAL_INT16( value , PC_WORD );   
  TEST_ASSERT_EQUAL_INT8( 4, length );  
}
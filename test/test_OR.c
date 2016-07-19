#include "unity.h"
#include "OR.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

uint8_t src;
void setUp(void)
{
  instantiateCPU();
  
  A = 0x9D;
  src = 0xAE;
  
  
  /**      0x9D     1001 1101
  *  |     0xAE     1010 1110
  *--------------------------
  *        0xBF     1011 1111
  *--------------------------
  */
 
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
}

void tearDown(void)
{
   free(cpu);
   free(ramBlock);
}


//Assembly : #byte | or A,#$55
void test_or_a_byte(void){
  uint8_t instr[] = {0XAB, src};
  
  TEST_ASSERT_EQUAL_INT8(2, or_a_byte(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(1, N); // is negative because bit 7 is 1 
}

//Assembly : shortmem | or A,$10
void test_or_a_shortmem(void){
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  
  MEM_WRITE_BYTE(addr, src);
  
  TEST_ASSERT_EQUAL_INT8(2, or_a_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}


//Assembly : longmem | or A,$1000
void test_or_a_longmem(void){
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE(0x1101, src);
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}


//Assembly : (X) | or A,(X)
void test_or_a_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(1, or_a_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : (shortoff,X) | or A,($10,X)
void test_or_a_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, or_a_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : (longoff,X) | or A,($1000,X)
void test_or_a_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : (Y) | or A,(Y)
void test_or_a_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(2, or_a_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : (shortoff,Y) | or A,($10,Y)
void test_or_a_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : (longoff,Y) | or A,($1000,Y)
void test_or_a_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, or_a_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : A  | (shortoff,SP) or A,($10,SP)
void test_or_a_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, or_a_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : [shortptr.w] | or A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_or_a_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : [longptr.w] | or A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_or_a_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA);  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(4, or_a_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : ([shortptr.w],X) | or A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_or_a_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

// Assembly : ([longptr.w],X) | or A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_or_a_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA);  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  MEM_WRITE_BYTE(0xAACC , src);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, or_a_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}

//Assembly : ([shortptr.w],Y) or A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_or_a_shortptr_w_y(void){
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, or_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xBF, A);
}
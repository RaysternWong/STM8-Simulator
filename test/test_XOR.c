#include "unity.h"
#include "XOR.h"
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
  *  ^     0xAE     1010 1110
  *--------------------------
  *        0x33     0011 0011
  *--------------------------
  */
 
  
  // Set the ramMemxory occupy the memxoryTable from 0000 to FFFF, fxor testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
}

void tearDown(void)
{
   free(cpu);
   free(ramBlock);
}


//Assembly : #byte | xor A,#$55
void test_xor_a_byte(void){
  uint8_t instr[] = {0XAB, src};
  
  TEST_ASSERT_EQUAL_INT8(2, xor_a_byte(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
  TEST_ASSERT_EQUAL_INT8(0, Z);
  TEST_ASSERT_EQUAL_INT8(0, N); // is positive because bit 7 is 0 
}

//Assembly : shortmem | xor A,$10
void test_xor_a_shortmem(void){
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  
  MEM_WRITE_BYTE(addr, src);
  
  TEST_ASSERT_EQUAL_INT8(2, xor_a_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}


//Assembly : longmem | xor A,$1000
void test_xor_a_longmem(void){
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE(0x1101, src);
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}


//Assembly : (X) | xor A,(X)
void test_xor_a_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(1, xor_a_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : (shortoff,X) | xor A,($10,X)
void test_xor_a_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, xor_a_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : (longoff,X) | xor A,($1000,X)
void test_xor_a_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : (Y) | xor A,(Y)
void test_xor_a_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(2, xor_a_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : (shortoff,Y) | xor A,($10,Y)
void test_xor_a_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : (longoff,Y) | xor A,($1000,Y)
void test_xor_a_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, xor_a_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : A  | (shortoff,SP) xor A,($10,SP)
void test_xor_a_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, xor_a_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : [shortptr.w] | xor A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_xor_a_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : [longptr.w] | xor A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_xor_a_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA);  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(4, xor_a_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : ([shortptr.w],X) | xor A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_xor_a_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

// Assembly : ([longptr.w],X) | xor A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_xor_a_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA);  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  MEM_WRITE_BYTE(0xAACC , src);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, xor_a_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}

//Assembly : ([shortptr.w],Y) xor A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_xor_a_shortptr_w_y(void){
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, xor_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x33, A);
}
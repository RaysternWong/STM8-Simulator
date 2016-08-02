#include "unity.h"
#include "LD.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>


void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  A = 0xAE;
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/*

    LD A,($12,SP)     | A ← M(SP+shortoff)

    LD ($12,SP),A     |M(SP+shortoff) ← A

    LD A, XH          |A ← XH

*/


//Assembly : shortmem | ld A,$10
void test_ld_a_to_shortmem(void){
  uint8_t shortMEM    = 0xAD;
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_to_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(shortMEM));
}


//Assembly : longmem | ld A,$1000
void test_ld_a_to_longmem(void){
  uint16_t longmem = 0x1101;
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(longmem));
}


//Assembly : (X) | ld A,(X)
void test_ld_a_to_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};
  
  TEST_ASSERT_EQUAL_INT8(1, ld_a_to_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X102B));
}

//Assembly : (shortoff,X) | ld A,($10,X)
void test_ld_a_to_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT8(2, ld_a_to_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X2B22));
}

//Assembly : (longoff,X) | ld A,($1000,X)
void test_ld_a_to_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X3c22));
}

//Assembly : (Y) | ld A,(Y)
void test_ld_a_to_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_to_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X102B));
}

//Assembly : (shortoff,Y) | ld A,($10,Y)
void test_ld_a_to_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X2B22));
}

//Assembly : (longoff,Y) | ld A,($1000,Y)
void test_ld_a_to_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, ld_a_to_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X3c22));
}

//Assembly : A  | (shortoff,SP) ld A,($10,SP)
void test_ld_a_to_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_to_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X2B22));
}

//Assembly : [shortptr.w] | ld A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_ld_a_to_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  

  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0xAABB));
}

//Assembly : [longptr.w] | ld A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_ld_a_to_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA);  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  

  TEST_ASSERT_EQUAL_INT8(4, ld_a_to_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0xAABB));
}

//Assembly : ([shortptr.w],X) | ld A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_to_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0x1122));
}

// Assembly : ([longptr.w],X) | ld A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_to_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA);  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, ld_a_to_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0XAACC));
}

//Assembly : ([shortptr.w],Y) ld A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_to_shortptr_w_y(void){
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_to_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, MEM_READ_BYTE(0X1122));
}
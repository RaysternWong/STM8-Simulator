#include "unity.h"
#include "CPL.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

uint8_t src;
void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  src = 0xAE;
  // result = 0xFF - 0xAE = 0x51
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/*
CPL ([$1234.w],X)

              M(M(longmem).w +X) ← FF - M(M(longmem).w+X)
                                              or
                                   M(M(longmem).w+X) cpl FF



*/


//Assembly : #byte | cpl A,#$55
void test_cpl_a(void){
  A = 0xAE;
  MEM_WRITE_BYTE(A, src);
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, cpl_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(A) );
}


//Assembly : shortmem | cpl A,$10
void test_cpl_shortmem(void){
  uint8_t shortMEM    = 0xAD;
  MEM_WRITE_BYTE(shortMEM, src);
  
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(2, cpl_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(shortMEM) );
}


//Assembly : longmem | cpl A,$1000
void test_cpl_longmem(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, src);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, cpl_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(longmem) );
}


//Assembly : (X) | cpl A,(X)
void test_cpl_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(1, cpl_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X102B) );
}

//Assembly : (shortoff,X) | cpl A,($10,X)
void test_cpl_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, cpl_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X2B22) );
}

//Assembly : (longoff,X) | cpl A,($1000,X)
void test_cpl_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, cpl_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X3c22) );
}

//Assembly : (Y) | cpl A,(Y)
void test_cpl_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(2, cpl_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X102B) );
}

//Assembly : (shortoff,Y) | cpl A,($10,Y)
void test_cpl_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, cpl_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X2B22) );
}

//Assembly : (longoff,Y) | cpl A,($1000,Y)
void test_cpl_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, cpl_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X3c22) );
}

//Assembly : A  | (shortoff,SP) cpl A,($10,SP)
void test_cpl_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, cpl_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0X2B22) );
}

//Assembly : [shortptr.w] | cpl A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_cpl_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA );  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(3, cpl_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0xAABB) );
}

//Assembly : [longptr.w] | cpl A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_cpl_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA );  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(4, cpl_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0xAABB) );
}

//Assembly : ([shortptr.w],X) | cpl A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cpl_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, cpl_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0x1122) );
}

// Assembly : ([longptr.w],X) | cpl A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cpl_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA );  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  MEM_WRITE_BYTE(0xAACC , src);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, cpl_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0xAACC) );
}

//Assembly : ([shortptr.w],Y) cpl A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cpl_shortptr_w_y(void){
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , src);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, cpl_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x51, MEM_READ_BYTE(0x1122) );
}
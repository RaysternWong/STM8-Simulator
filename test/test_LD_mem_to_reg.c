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


//Assembly : #byte | ld A,#$55
void test_ld_a_byte(void){

  MEM_WRITE_BYTE(A, 0xAE);
  uint8_t instr[] = {0XAB, 0xAE};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_byte(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A);
}


//Assembly : shortmem | ld A,$10
void test_ld_a_shortmem(void){
  uint8_t shortMEM    = 0xAD;
  MEM_WRITE_BYTE(shortMEM, 0xAE);
  
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A);
}


//Assembly : longmem | ld A,$1000
void test_ld_a_longmem(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_BYTE(longmem, 0xAE);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(3, ld_a_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}


//Assembly : (X) | ld A,(X)
void test_ld_a_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , 0xAE);
  
  TEST_ASSERT_EQUAL_INT8(1, ld_a_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : (shortoff,X) | ld A,($10,X)
void test_ld_a_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , 0xAE);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : (longoff,X) | ld A,($1000,X)
void test_ld_a_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , 0xAE);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : (Y) | ld A,(Y)
void test_ld_a_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , 0xAE);
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A);
}

//Assembly : (shortoff,Y) | ld A,($10,Y)
void test_ld_a_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  0xAE);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : (longoff,Y) | ld A,($1000,Y)
void test_ld_a_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3c22 , 0xAE);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, ld_a_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : A  | (shortoff,SP) ld A,($10,SP)
void test_ld_a_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , 0xAE);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ld_a_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, A);
}

//Assembly : [shortptr.w] | ld A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_ld_a_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA );  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , 0xAE);  
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : [longptr.w] | ld A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_ld_a_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA );  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , 0xAE);  
  
  TEST_ASSERT_EQUAL_INT8(4, ld_a_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : ([shortptr.w],X) | ld A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , 0xAE);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, A);
}

// Assembly : ([longptr.w],X) | ld A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA );  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  MEM_WRITE_BYTE(0xAACC , 0xAE);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, ld_a_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}

//Assembly : ([shortptr.w],Y) ld A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_ld_a_shortptr_w_y(void){
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_BYTE(0x1122 , 0xAE);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ld_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE, A );
}
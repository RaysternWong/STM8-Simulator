#include "unity.h"
#include "NEG.h"
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
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

/**
  M(M(longmem) + X) ←  00 - M(M(longmem) + X)
  
  result = 0- src = 0x52
*/


//Assembly : #byte | neg A,#$55
void test_neg_a(void){
  A = 0x9D;
  MEM_WRITE_BYTE( A , src);
  
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, neg_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(A));
}



// Assembly : shortmem | neg A,$10
void test_neg_shortmem(void){
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  
  MEM_WRITE_BYTE(addr, src);
  
  TEST_ASSERT_EQUAL_INT8(2, neg_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(addr));
}


// Assembly : longmem | neg A,$1000
void test_neg_longmem(void){
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE(0x1101, src);
  
  TEST_ASSERT_EQUAL_INT8(4, neg_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0x1101));
}


// Assembly : (X) | neg A,(X)
void test_neg_x(void){
  SET_X(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(1, neg_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X102B));
}

// Assembly : (shortoff,X) | neg A,($10,X)
void test_neg_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, neg_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X2B22));
}

// Assembly : (longoff,X) | neg A,($1000,X)
void test_neg_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3C22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, neg_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X3C22));
}

// Assembly : (Y) | neg A,(Y)
void test_neg_y(void){
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE(0X102B , src);
  
  TEST_ASSERT_EQUAL_INT8(2, neg_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X102B));
}

// Assembly : (shortoff,Y) | neg A,($10,Y)
void test_neg_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE( 0X2B22 ,  src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, neg_shortoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X2B22));
}

// Assembly : (longoff,Y) | neg A,($1000,Y)
void test_neg_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_BYTE(0X3C22 , src);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, neg_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X3C22));
}

// Assembly : A  | (shortoff,SP) neg A,($10,SP)
void test_neg_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_BYTE(0X2B22 , src);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, neg_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0X2B22));
}

// Assembly : [shortptr.w] | neg A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_neg_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_BYTE(0xAABB , src);  
  
  TEST_ASSERT_EQUAL_INT8(3, neg_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0x52, MEM_READ_BYTE(0xAABB));
}
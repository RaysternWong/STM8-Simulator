#include "unity.h"
#include "LDW.h"
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

//--------------------test load mem word to X------------------

void test_ldw_x_word(void){
  uint8_t instr[] = {0XAB, 0xAE, 0x11};
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_word(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE11, X);
}

void test_ldw_x_shortmem(void){
  uint8_t shortMEM    = 0xAD;
  MEM_WRITE_WORD(shortMEM, 0xAE11);
  
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_shortmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE11, X);
}

void test_ldw_x_longmem(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_WORD(longmem, 0xAE11);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(3, ldw_x_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_x(void){
  SET_X(0X102B);
  
  uint8_t instr[] = {0XFB};

  MEM_WRITE_WORD(0X102B , 0xAE11);
  
  TEST_ASSERT_EQUAL_INT8(1, ldw_x_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_WORD(0X2B22 , 0xAE11);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_WORD(0X3c22 , 0xAE11);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_WORD(0X2B22 , 0xAE11);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE11, X);
}

void test_ldw_x_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA );  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_WORD(0xAABB , 0xAE11);  
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA );  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  
  MEM_WRITE_WORD(0xAABB , 0xAE11);  
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_x_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE11, X );
}

void test_ldw_x_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_WORD(0x1122 , 0xAE11);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE11, X);
}

void test_ldw_x_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA );  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  MEM_WRITE_WORD(0xAACC , 0xAE11);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_x_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE11, X );
}

//--------------------test load mem word to Y------------------
void test_ldw_y_word(void){
  uint8_t instr[] = {0XAB, 0xAE, 0x11};
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_y_word(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE11, Y);
}

void test_ldw_y_shortmem(void){
  uint8_t shortMEM    = 0xAD;
  MEM_WRITE_WORD(shortMEM, 0xAE11);
  
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_shortmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE11, Y);
}

void test_ldw_y_longmem(void){
  uint16_t longmem = 0x1101;
  MEM_WRITE_WORD(longmem, 0xAE11);
  
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, ldw_y_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE11, Y );
}

void test_ldw_y_y(void){
  SET_Y(0X102B);
  
  uint8_t instr[] = {0XFB};

  MEM_WRITE_WORD(0X102B , 0xAE11);
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_y_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xAE11, Y );
}

void test_ldw_y_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_WORD(0X2B22 , 0xAE11);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_shortoff_y(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE11, Y );
}

void test_ldw_y_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  MEM_WRITE_WORD(0X3c22 , 0xAE11);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_y_longoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xAE11, Y );
}

void test_ldw_y_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  MEM_WRITE_WORD(0X2B22 , 0xAE11);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_y_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE11, Y);
}

void test_ldw_y_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA );  
  MEM_WRITE_BYTE(0X14 , 0xBB);  
  MEM_WRITE_WORD(0xAABB , 0xAE11);  
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT8(0xAE11, Y );
}

void test_ldw_y_shortptr_w_y(void){ 
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  MEM_WRITE_WORD(0x1122 , 0xAE11);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_shortptr_w_y(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE11, Y);
}




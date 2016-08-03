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
  SET_X(0xAE33);
  SET_Y(0xAE33);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}



void test_ldw_x_to_shortmem(void){
  uint8_t shortMEM = 0xAD;
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_to_shortmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(shortMEM));
}


void test_ldw_x_to_longmem(void){
  uint16_t longmem = 0x1101;
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(3, ldw_x_to_longmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(longmem));
}


void test_ldw_y_to_x(void){
  SET_X(0x33);
  MEM_WRITE_WORD(X, 0x102B);
  uint8_t instr[] = {0XFB};
  
  TEST_ASSERT_EQUAL_INT8(1, ldw_y_to_x(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X102B));
}

void test_ldw_y_to_shortoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT8(2, ldw_y_to_shortoff_x(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X2B22));
}

void test_ldw_y_to_longoff_x(void){
  SET_X(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_to_longoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X3c22));
}

void test_ldw_x_to_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_to_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X2B22));
}

void test_ldw_x_to_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  

  TEST_ASSERT_EQUAL_INT8(3, ldw_x_to_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0xAABB));
}

void test_ldw_x_to_longptr_w(void){
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  MEM_WRITE_BYTE(0X1315 , 0xAA);  
  MEM_WRITE_BYTE(0X1316 , 0xBB);  

  TEST_ASSERT_EQUAL_INT8(4, ldw_x_to_longptr_w(instr)); 
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0xAABB));
}

void test_ldw_y_to_shortptr_w_x(void){ 
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_to_shortptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0x1122));
}

void test_ldw_y_to_longptr_w_x(void){
  SET_X(0X0011);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  MEM_WRITE_BYTE(0X1300 , 0xAA);  
  MEM_WRITE_BYTE(0X1301 , 0xBB);  
  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_y_to_longptr_w_x(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0XAACC));
}

// test for Y

void test_ldw_y_to_shortmem(void){
  uint8_t shortMEM = 0xAD;
  uint8_t instr[] = {0XBB, shortMEM};
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_y_to_shortmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(shortMEM));
}


void test_ldw_y_to_longmem(void){
  uint16_t longmem = 0x1101;
  uint8_t instr[] = {0XBB, 0x11, 0x01};

  TEST_ASSERT_EQUAL_INT8(4, ldw_y_to_longmem(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(longmem));
}


void test_ldw_x_to_y(void){
  SET_Y(0x33);
  MEM_WRITE_WORD(Y, 0x102B);
  uint8_t instr[] = {0XFB};
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_x_to_y(instr));
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X102B));
}

void test_ldw_x_to_shortoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_to_shortoff_y(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X2B22));
}

void test_ldw_x_to_longoff_y(void){
  SET_Y(0X2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, ldw_x_to_longoff_y(instr)); 
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X3c22));
}

void test_ldw_y_to_shortoff_sp(void){
  SET_SP(0X2B11);
  uint8_t instr[] = {0XFB, 0X11};
  
  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, ldw_y_to_shortoff_sp(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0X2B22));
}

void test_ldw_y_to_shortptr_w(void){
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0xAA);  
  MEM_WRITE_BYTE(0X14 , 0xBB);  

  TEST_ASSERT_EQUAL_INT8(3, ldw_y_to_shortptr_w(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0xAABB));
}


void test_ldw_x_to_shortptr_w_y(void){ 
  SET_Y(0X0011);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE(0X13 , 0x11);  
  MEM_WRITE_BYTE(0X14 , 0x11);  
  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, ldw_x_to_shortptr_w_y(instr));  
  TEST_ASSERT_EQUAL_INT16(0xAE33, MEM_READ_WORD(0x1122));
}




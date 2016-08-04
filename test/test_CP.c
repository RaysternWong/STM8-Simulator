#include "unity.h"
#include "CP.h"
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


//Assembly : #byte | cp A,#$55
void test_cp_a_byte(void)
{
  A = 0x09;
  C = 0;
  uint8_t instr[] = {0XAB, 0X05};
  
  TEST_ASSERT_EQUAL(2, cp_a_byte(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}


//Assembly : shortmem | cp A,$10
void test_cp_a_shortmem(void)
{
  A               = 0x09;
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( addr,  0x05);
  
  TEST_ASSERT_EQUAL(2, cp_a_shortmem(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}


//Assembly : longmem | cp A,$1000
void test_cp_a_longmem(void)
{
  A               = 0x09;
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01; 
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  0x05);
  
  TEST_ASSERT_EQUAL(3, cp_a_longmem(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}


//Assembly : (X) | cp A,(X)
void test_cp_a_x(void)
{
  A = 0x09;
  SET_X(0x102B);
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(1, cp_a_x(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}


//Assembly : (shortoff,X) | cp A,($10,X)
void test_cp_a_shortoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, cp_a_shortoff_x(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}

//Assembly : (longoff,X) | cp A,($1000,X)
void test_cp_a_longoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3c22 ,  0x04);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(3, cp_a_longoff_x(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}

//Assembly : (Y) | cp A,(Y)
void test_cp_a_y(void)
{
  A = 0x09;
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(2, cp_a_y(instr)); 
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (shortoff,Y) | cp A,($10,Y)
void test_cp_a_shortoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(3, cp_a_shortoff_y(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (longoff,Y) | cp A,($1000,Y)
void test_cp_a_longoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, cp_a_longoff_y(instr));
  
}

//Assembly : A  | (shortoff,SP) cp A,($10,SP)
void test_cp_a_shortoff_sp(void)
{
  A = 0x09;
  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, cp_a_shortoff_sp(instr));
  
}

//Assembly : [shortptr.w] | cp A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_cp_a_shortptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(3, cp_a_shortptr_w(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : [longptr.w] | cp A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_cp_a_longptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(4, cp_a_longptr_w(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}

//Assembly : ([shortptr.w],X) | cp A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cp_a_shortptr_w_x(void)
{
  A = 0x09;
  SET_X(0X11);
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, cp_a_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

// Assembly : ([longptr.w],X) | cp A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cp_a_longptr_w_x(void)
{
  A = 0x09;
  SET_X(0x102B);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , 0x05);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL(4, cp_a_longptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}

//Assembly : ([shortptr.w],Y) cp A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_cp_a_shortptr_w_y(void)
{
  A = 0x09; 
  SET_Y(0x11);
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, cp_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

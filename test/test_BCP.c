#include "unity.h"
#include "BCP.h"
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
  CLEAR_ALL_FLAGS;
  clearConditionCodeRegister(&(cpu->ccr));
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}


//Assembly : #byte | bcp A,#$55
void test_bcp_a_byte(void)
{
  A = 0x0;
  uint8_t instr[] = {0XAB, 0X05};
  
  TEST_ASSERT_EQUAL(2, bcp_a_byte(instr));
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(1, Z); // A is 0, so the AND result also 0
}


//Assembly : shortmem | bcp A,$10
void test_bcp_a_shortmem(void)
{
  A               = 0x88;
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( addr,  0x80);
  
  TEST_ASSERT_EQUAL(2, bcp_a_shortmem(instr));
  TEST_ASSERT_EQUAL(1, N);  //0x88 & 0x80 = 0x80 , bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z); 

}


//Assembly : longmem | bcp A,$1000
void test_bcp_a_longmem(void)
{
  A               = 0x09;
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01; 
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  0x05);
  
  TEST_ASSERT_EQUAL(3, bcp_a_longmem(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}


//Assembly : (X) | bcp A,(X)
void test_bcp_a_x(void)
{
  A = 0x09;
  SET_X(0x102B);
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(1, bcp_a_x(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}


//Assembly : (shortoff,X) | bcp A,($10,X)
void test_bcp_a_shortoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, bcp_a_shortoff_x(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (longoff,X) | bcp A,($1000,X)
void test_bcp_a_longoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(3, bcp_a_longoff_x(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (Y) | bcp A,(Y)
void test_bcp_a_y(void)
{
  A = 0x09;
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(2, bcp_a_y(instr)); 
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (shortoff,Y) | bcp A,($10,Y)
void test_bcp_a_shortoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(3, bcp_a_shortoff_y(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : (longoff,Y) | bcp A,($1000,Y)
void test_bcp_a_longoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, bcp_a_longoff_y(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : A  | (shortoff,SP) bcp A,($10,SP)
void test_bcp_a_shortoff_sp(void)
{
  A = 0x09;
  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, bcp_a_shortoff_sp(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : [shortptr.w] | bcp A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_bcp_a_shortptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(3, bcp_a_shortptr_w(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : [longptr.w] | bcp A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_bcp_a_longptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(4, bcp_a_longptr_w(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : ([shortptr.w],X) | bcp A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_bcp_a_shortptr_w_x(void)
{
  A = 0x09;
  SET_X(0X11);
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, bcp_a_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

// Assembly : ([longptr.w],X) | bcp A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_bcp_a_longptr_w_x(void)
{
  A = 0x09;
  SET_X(0x11);
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , 0x05);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL(4, bcp_a_longptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}

//Assembly : ([shortptr.w],Y) bcp A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_bcp_a_shortptr_w_y(void)
{
  A = 0x09; 
  SET_Y(0x11);
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, bcp_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL(0, Z);  //0x09 & 0x05 = 0x01 , neither 0 or negative
  TEST_ASSERT_EQUAL(0, C);
}
#include "unity.h"
#include "SUB.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>


void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
}

void tearDown(void)
{
   free(cpu);
   free(ramBlock);
}


//Assembly : #byte | sub A,#$55
void test_sub_a_byte(void)
{
  A = 0x09;
  uint8_t instr[] = {0XAB, 0X05};
  
  TEST_ASSERT_EQUAL(2, sub_a_byte(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}


//Assembly : shortmem | sub A,$10
void test_sub_a_shortmem(void)
{
  A               = 0x09;
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( addr,  0x05);
  
  TEST_ASSERT_EQUAL(2, sub_a_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}


//Assembly : longmem | sub A,$1000
void test_sub_a_longmem(void)
{
  A               = 0x09;
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01; 
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  0x05);
  
  TEST_ASSERT_EQUAL(3, sub_a_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}


//Assembly : (X) | sub A,(X)
void test_sub_a_x(void)
{
  A = 0x09;
  XH = 0X10;
  XL = 0X2B;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(1, sub_a_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A); 
}


//Assembly : (shortoff,X) | sub A,($10,X)
void test_sub_a_shortoff_x(void)
{
  A = 0x09;
  XH = 0X2B;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, sub_a_shortoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A); 
}

//Assembly : (longoff,X) | sub A,($1000,X)
void test_sub_a_longoff_x(void)
{
  A = 0x09;
  XH = 0X2B;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3c22 ,  0x04);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(3, sub_a_longoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x05, A); 
}

//Assembly : (Y) | sub A,(Y)
void test_sub_a_y(void)
{
  A = 0x09;
  YH = 0X10;
  YL = 0X2B;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(2, sub_a_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : (shortoff,Y) | sub A,($10,Y)
void test_sub_a_shortoff_y(void)
{
  A = 0x09;
  YH = 0X2B;
  YL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(3, sub_a_shortoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : (longoff,Y) | sub A,($1000,Y)
void test_sub_a_longoff_y(void)
{
  A = 0x09;
  YH = 0X2B;
  YL = 0X11;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, sub_a_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : A  | (shortoff,SP) sub A,($10,SP)
void test_sub_a_shortoff_sp(void)
{
  A = 0x09;
  SPH = 0X2B;
  SPL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, sub_a_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : [shortptr.w] | sub A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_sub_a_shortptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(3, sub_a_shortptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : [longptr.w] | sub A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_sub_a_longptr_w(void)
{
  A = 0x09;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(4, sub_a_longptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : ([shortptr.w],X) | sub A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_sub_a_shortptr_w_x(void)
{
  A = 0x09;
  XH = 0X00;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, sub_a_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

// Assembly : ([longptr.w],X) | sub A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_sub_a_longptr_w_x(void)
{
  A = 0x09;
  XH = 0X00;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , 0x05);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL(4, sub_a_longptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A);
}

//Assembly : ([shortptr.w],Y) sub A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_sub_a_shortptr_w_y(void)
{
  A = 0x09; 
  YH = 0X00;
  YL = 0X11;
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, sub_a_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x04, A); 
}

void test_sub_sp_byte(void)
{
  SET_SP(0x1100);
  uint8_t instr[] = {0XAB, 0X02};
  
  TEST_ASSERT_EQUAL(2, sub_sp_byte(instr));
  TEST_ASSERT_EQUAL_INT16(0x10FE, SP);
}
#include "unity.h"
#include "ADC.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>
#include "ErrorObject.h"
uint8_t offSet1, offSet2;

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0, 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 

  A = 0x01;
  C = 0;    // default carry is 0
  
  SET_X(0X0040);
  SET_Y(0x1170);
  SET_SP(0x2290);
 
  MEM_WRITE_BYTE( X  ,  0x07);
  MEM_WRITE_BYTE( Y  ,  0x08);
  MEM_WRITE_BYTE( SP ,  0x09);
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}

//Assembly : #byte | adc A,#$55
void test_adc_a_byte(void)
{
  uint8_t instr[] = {0XAB, 0X05};
  C = 1;

  int length = adc_a_byte(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x07, A);  // 1 + 1 + 5 = 7   (A+ C+ 5= 7)
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : shortmem | adc A,$10
void test_adc_a_shortmem(void)
{

  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  
  MEM_WRITE_BYTE( addr,  0x05);
  
  int length = adc_a_shortmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(2, length);
}


//Assembly : longmem | adc A,$1000
void test_adc_a_longmem(void)
{ 
  offSet1 = 0x12;
  offSet2 = 0x3A;
  MEM_WRITE_BYTE( 0X123A  ,  0x07);


  uint8_t instr[] = {0XBB, offSet1, offSet2};
  
  int length = adc_a_longmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(3, length);
}


//Assembly : (X) | adc A,(X)
void test_adc_a_x(void)
{
  uint8_t instr[] = {0XFB};

  int length = adc_a_x(instr);
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(1, length);
}

//Assembly : (shortoff,X) | adc A,($10,X)
void test_adc_a_shortoff_x(void)
{
  uint8_t instr[] = {0XFB, 0X11};
  
  uint16_t addrHoldingData = X + 0x11;
  MEM_WRITE_BYTE( addrHoldingData ,  0x02);  
  
  int length = adc_a_shortoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, length);
}


//Assembly : (longoff,X) | adc A,($1000,X)
void test_adc_a_longoff_x(void)
{
  uint8_t instr[] = {0XFB, 0X12, 0xBB};
  
  uint16_t addrHoldingData = X + 0x12BB;
  MEM_WRITE_BYTE( addrHoldingData ,  0x04);  
  
  int length = adc_a_longoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x05, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : (Y) | adc A,(Y)
void test_adc_a_y(void)
{
  uint8_t instr[] = {0XFB};

  MEM_WRITE_BYTE( Y ,  0x02);
  
  int length = adc_a_y(instr);
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, length);
}


//Assembly : (shortoff,Y) | adc A,($10,Y)
void test_adc_a_shortoff_y(void)
{

  uint8_t instr[] = {0XFB, 0X11};
  
  uint16_t addrHoldingData = Y + 0x11;
  MEM_WRITE_BYTE( addrHoldingData ,  0x03);
  
  int length = adc_a_shortoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x04, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : (longoff,Y) | adc A,($1000,Y)
void test_adc_a_longoff_y(void)
{
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  uint16_t addrHoldingData = Y + 0x1111;
  MEM_WRITE_BYTE( addrHoldingData ,  0x07);
 
  int length = adc_a_longoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(4, length);
}

//Assembly : (shortoff,SP) | adc A,($10,SP)
void test_adc_a_shortoff_sp_given_A_0x01_address_contain_0x02_should_get0x03_and_return_3(void)
{
  uint8_t instr[] = {0XFB, 0X11};
  
  uint16_t addrHoldingData = SP + 0x11;
  MEM_WRITE_BYTE( addrHoldingData ,  0x07);
  
  int length = adc_a_shortoff_sp(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : [shortptr.w] | adc A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_adc_a_shortptr_w_given_A_0x01_address_contain_0x04_should_get0x05_and_return_3(void)
{
  uint8_t instr[] = {0XFB, 0X12};
  
  MEM_WRITE_BYTE( 0X12 , 0x01);  
  MEM_WRITE_BYTE( 0X13 , 0xBB);  
  MEM_WRITE_BYTE( 0x01BB , 0x04);  
  
  int length = adc_a_shortptr_w(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x05, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : [longptr.w] | adc A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_adc_a_longptr_w_given_A_0x01_address_contain_0x09_should_get0x0A_and_return_4(void)
{

  uint8_t instr[] = {0XFB, 0X00, 0X15};
  
  MEM_WRITE_BYTE( 0X0015 , 0x12);  
  MEM_WRITE_BYTE( 0X0016 , 0xBB);  
  MEM_WRITE_BYTE( 0x12BB , 0x09);  
  
  int length = adc_a_longptr_w(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x0A, A);
  TEST_ASSERT_EQUAL(4, length);
}

//Assembly : ([shortptr.w],X) | adc A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_adc_a_shortptr_w_x_given_A_0x01_address_contain_0x05_should_get0x06_and_return_3(void)
{
  uint8_t instr[] = {0XFB, 0X00};
  
  MEM_WRITE_BYTE( 0X00 , 0x12);  
  MEM_WRITE_BYTE( 0X01 , 0x11);  
  
  uint16_t addrHoldingData = X + 0x1211;
  
  MEM_WRITE_BYTE( addrHoldingData , 0x05);  
  
  int length = adc_a_shortptr_w_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(3, length);
}

// Assembly : ([longptr.w],X) | adc A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_adc_a_longptr_w_x_given_A_0x01_address_contain_0x02_should_get0x03_and_return_4(void)
{
  uint8_t instr[] = {0XFB, 0X00, 0X00};
  
  MEM_WRITE_BYTE( 0X0000 , 0x0A);  
  MEM_WRITE_BYTE( 0X0001 , 0xBB);  
  
  uint16_t addrHoldingData = X + 0x0ABB;
  MEM_WRITE_BYTE( addrHoldingData , 0x02);  
  
  int length = adc_a_longptr_w_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(4, length);
}


//Assembly : ([shortptr.w],Y) adc A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_adc_a_shortptr_w_y_given_A_0x01_address_contain_0x05_should_get0x06_and_return_3(void)
{
  uint8_t instr[] = {0XFB, 0X00};
  
  MEM_WRITE_BYTE( 0X00 , 0x12);  
  MEM_WRITE_BYTE( 0X01 , 0x11);  
  
  uint16_t addrHoldingData = Y + 0x1211;
  
  MEM_WRITE_BYTE( addrHoldingData , 0x05);  
  
  int length = adc_a_shortptr_w_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(3, length);;
}

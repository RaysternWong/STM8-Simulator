#include "unity.h"
#include "ADD.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>

#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)


void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
   free(cpu);
}

//Assembly : #byte | ADD A,#$55
void test_add_a_byte_given_A_0x01_byte_is_0x05_should_get_0x06_and_return_2(void)
{
  A = 0x01;
  uint8_t instr[] = {0XAB, 0X05};
  
  int length = add_a_byte(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : shortmem | ADD A,$10
void test_add_a_shortmem_given_A_0x01_address_contain_0x05_should_get_0x06_and_return_2(void)
{
  A               = 0x01;
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  
  writeValueToTheAddress( addr,  0x05);
  
  int length = add_a_shortmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : longmem | ADD A,$1000
void test_add_a_longmem_given_A_0x01_address_contain_0x05_should_get_0x06_and_return_3(void)
{
  A               = 0x01;
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  
  writeValueToTheAddress( 0x1101,  0x05);
  
  int length = add_a_longmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : (X) | ADD A,(X)
void test_add_a_x_given_A_0x01_address_contain_0x07_should_get0x08_and_return_1(void)
{
  A = 0x01;
  XH = 0X10;
  XL = 0X2B;
  uint8_t instr[] = {0XFB};

  writeValueToTheAddress( 0X102B ,  0x07);
  
  int length = add_a_x(instr);
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(1, length);
}

//Assembly : (shortoff,X) | ADD A,($10,X)
void test_add_a_shortoff_x_given_A_0x01_address_contain_0x02_should_get0x03_and_return_2(void)
{
  A = 0x01;
  XH = 0X2B;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  
  writeValueToTheAddress( 0X2B22 ,  0x02);  //0x2B11 + 0X11 = 0X2B22
  
  int length = add_a_shortoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : (longoff,X) | ADD A,($1000,X)
void test_add_a_longoff_x_given_A_0x01_address_contain_0x04_should_get0x05_and_return_3(void)
{
  A = 0x01;
  XH = 0X2B;
  XL = 0X11;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  writeValueToTheAddress( 0X3c22 ,  0x04);  //0x2B11 + 0X1111 = 0X3c22
  
  int length = add_a_longoff_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x05, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : (Y) | ADD A,(Y)
void test_add_a_y_given_A_0x01_address_contain_0x02_should_get0x03_and_return_2(void)
{
  A = 0x01;
  YH = 0X10;
  YL = 0X2B;
  uint8_t instr[] = {0XFB};

  writeValueToTheAddress( 0X102B ,  0x02);
  
  int length = add_a_y(instr);
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : (shortoff,Y) | ADD A,($10,Y)
void test_add_a_shortoff_y_given_A_0x01_address_contain_0x03_should_get0x04_and_return_3(void)
{
  A = 0x01;
  YH = 0X2B;
  YL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  
  writeValueToTheAddress( 0X2B22 ,  0x03);  //0x2B11 + 0X11 = 0X2B22
  
  int length = add_a_shortoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x04, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : (longoff,Y) | ADD A,($1000,Y)
void test_add_a_longoff_y_given_A_0x01_address_contain_0x07_should_get0x08_and_return_4(void)
{
  A = 0x01;
  YH = 0X2B;
  YL = 0X11;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  
  writeValueToTheAddress( 0X3c22 ,  0x07);  //0x2B11 + 0X1111 = 0X3c22
  
  int length = add_a_longoff_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x08, A);
  TEST_ASSERT_EQUAL(4, length);
}

//Assembly : A  | (shortoff,SP) ADD A,($10,SP)
void test_add_a_shortoff_sp_given_A_0x01_address_contain_0x02_should_get0x03_and_return_3(void)
{
  A = 0x01;
  SPH = 0X2B;
  SPL = 0X11;
  uint8_t instr[] = {0XFB, 0X11};
  
  writeValueToTheAddress( 0X2B22 ,  0x02);  //0x2B11 + 0X11 = 0X2B22
  
  int length = add_a_shortoff_sp(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(2, length);
}

//Assembly : [shortptr.w] | ADD A,[$10.w]
// Please refer this instruction in page 46 of stm8 programming manual
void test_add_a_shortptr_w_given_A_0x01_address_contain_0x04_should_get0x05_and_return_3(void)
{
  A = 0x01;

  uint8_t instr[] = {0XFB, 0X13};
  
  writeValueToTheAddress( 0X13 , 0xAA);  
  writeValueToTheAddress( 0X14 , 0xBB);  
  writeValueToTheAddress( 0xAABB , 0x04);  
  
  int length = add_a_shortptr_w(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x05, A);
  TEST_ASSERT_EQUAL(3, length);
}

//Assembly : [longptr.w] | ADD A,[$1000.w]
// Please refer this instruction in page 47 of stm8 programming manual
void test_add_a_longptr_w_given_A_0x01_address_contain_0x09_should_get0x0A_and_return_4(void)
{
  A = 0x01;

  uint8_t instr[] = {0XFB, 0X13, 0X15};
  
  writeValueToTheAddress( 0X1315 , 0xAA);  
  writeValueToTheAddress( 0X1316 , 0xBB);  
  writeValueToTheAddress( 0xAABB , 0x09);  
  
  int length = add_a_longptr_w(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x0A, A);
  TEST_ASSERT_EQUAL(4, length);
}

//Assembly : ([shortptr.w],X) | ADD A,([$10.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_add_a_shortptr_w_x_given_A_0x01_address_contain_0x05_should_get0x06_and_return_3(void)
{
  A = 0x01;
  
  XH = 0X00;
  XL = 0X11;

  uint8_t instr[] = {0XFB, 0X13};
  
  writeValueToTheAddress( 0X13 , 0x11);  
  writeValueToTheAddress( 0X14 , 0x11);  
  writeValueToTheAddress( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  int length = add_a_shortptr_w_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(3, length);
}

// Assembly : ([longptr.w],X) | ADD A,([$1000.w],X)
// Please refer this instruction in page 50 of stm8 programming manual
void test_add_a_longptr_w_x_given_A_0x01_address_contain_0x02_should_get0x03_and_return_4(void)
{
  A = 0x01;
  
  XH = 0X00;
  XL = 0X11;

  uint8_t instr[] = {0XFB, 0X13, 0X00};
  
  writeValueToTheAddress( 0X1300 , 0xAA);  
  writeValueToTheAddress( 0X1301 , 0xBB);  
  writeValueToTheAddress( 0xAACC , 0x02);  // 0XAABB + 0X11 = 0XAACC
  
  int length = add_a_longptr_w_x(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x03, A);
  TEST_ASSERT_EQUAL(4, length);
}

//Assembly : ([shortptr.w],Y) ADD A,([$10.w],Y)
// Please refer this instruction in page 50 of stm8 programming manual
void test_add_a_shortptr_w_y_given_A_0x01_address_contain_0x05_should_get0x06_and_return_3(void)
{
  A = 0x01;
  
  YH = 0X00;
  YL = 0X11;

  uint8_t instr[] = {0XFB, 0X13};
  
  writeValueToTheAddress( 0X13 , 0x11);  
  writeValueToTheAddress( 0X14 , 0x11);  
  writeValueToTheAddress( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  int length = add_a_shortptr_w_y(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(3, length);
}
#include "unity.h"
#include "TNZ.h"
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


void test_tnz_a(void)
{
  A = 0x88;
  N = 0;
  Z = 1;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL(1, tnz_a(instr));

  TEST_ASSERT_EQUAL(1, N); // A is negative , because bit 7 is 1
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortmem(void)
{
  uint8_t addr    = 0xAD;
  N = 1;
  Z = 0;
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( addr,  0);
  
  TEST_ASSERT_EQUAL(2, tnz_shortmem(instr));
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(1, Z); //the byte store in addr is 0
}

void test_tnz_longmem(void)
{
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01; 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  0x05);
  
  TEST_ASSERT_EQUAL(4, tnz_longmem(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_x(void)
{
  A = 0x09;
  SET_X(0x102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(1, tnz_x(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, tnz_shortoff_x(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_longoff_x(void)
{
  A = 0x09;
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3c22 ,  0x04);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, tnz_longoff_x(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x4 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_y(void)
{
  A = 0x09;
  SET_Y(0X102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(2, tnz_y(instr)); 
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(3, tnz_shortoff_y(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_longoff_y(void)
{
  A = 0x09;
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, tnz_longoff_y(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

//Assembly : A  | (shortoff,SP) cp A,($10,SP)
void test_tnz_shortoff_sp(void)
{
  A = 0x09;
  SET_SP(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, tnz_shortoff_sp(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortptr_w(void)
{
  A = 0x09;
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(3, tnz_shortptr_w(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_longptr_w(void)
{
  A = 0x09;
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(4, tnz_longptr_w(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortptr_w_x(void)
{
  A = 0x09;
  SET_X(0X11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, tnz_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_longptr_w_x(void)
{
  A = 0x09;
  SET_X(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , 0x05);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL(4, tnz_longptr_w_x(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

void test_tnz_shortptr_w_y(void)
{
  A = 0x09; 
  SET_Y(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, tnz_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL(0, N);  //0x5 is not zero not negative
  TEST_ASSERT_EQUAL(0, Z); 
}

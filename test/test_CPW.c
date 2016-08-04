#include "unity.h"
#include "CPW.h"
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

void test_cpw_x_word(void)
{
  SET_X(0x0122);
  uint8_t instr[] = {0XAB, 0x0, 0X05};
  
  TEST_ASSERT_EQUAL(3, cpw_x_word(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}


void test_cpw_x_shortmem(void)
{
  SET_X(0x0122);
  uint8_t addr    = 0xAD;
  uint8_t instr[] = {0XBB, addr};
  MEM_WRITE_BYTE( addr,  0x05);
  
  TEST_ASSERT_EQUAL(2, cpw_x_shortmem(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

void test_cpw_x_longmem(void)
{
  SET_X(0x0122);
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01; 
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  MEM_WRITE_BYTE( 0x1101,  0x05);
  
  TEST_ASSERT_EQUAL(3, cpw_x_longmem(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

void test_cpw_x_y(void)
{
  SET_X(0x0122);
  SET_Y(0X102B);
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  0x05);
  
  TEST_ASSERT_EQUAL(2, cpw_x_y(instr)); 
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

void test_cpw_x_shortoff_y(void)
{
  SET_X(0x0122);
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(3, cpw_x_shortoff_y(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

void test_cpw_x_longoff_y(void)
{
  SET_X(0x0122);
  SET_Y(0x2B11);
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3c22 ,  0x05);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL(4, cpw_x_longoff_y(instr));
  
}

void test_cpw_x_shortoff_sp(void)
{
  SET_X(0x0122);
  SET_SP(0x2B11);
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  0x05);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL(2, cpw_x_shortoff_sp(instr));
  
}

void test_cpw_x_shortptr_w(void)
{
  SET_X(0x0122);
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(3, cpw_x_shortptr_w(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}

void test_cpw_x_longptr_w(void)
{
  SET_X(0x0122);
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , 0x05);  
  
  TEST_ASSERT_EQUAL(4, cpw_x_longptr_w(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C); 
}

void test_cpw_x_shortptr_w_y(void)
{
  SET_X(0x0122);
  SET_Y(0x11);
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , 0x05);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL(3, cpw_x_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL(0, V); 
  TEST_ASSERT_EQUAL(0, N); 
  TEST_ASSERT_EQUAL(0, Z); 
  TEST_ASSERT_EQUAL(0, C);
}
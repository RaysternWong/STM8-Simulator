#include "unity.h"
#include "SRL.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>


uint8_t value;
void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  
  value = 0xA6;
  
  /**
        0xA6    1010  0110    
                bit 0 is set to C, then shift right one time
        0x53    0101  0011
  
         C = 0
  */
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_srl_a(void){
  A = value;
  N = 1;
  Z = 1;
  C = 0;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, srl_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, A); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_shortmem(void){

  N = 1;
  Z = 0;
  uint8_t instr[] = {0XBB, 0xAD};
  MEM_WRITE_BYTE( 0xAD,  0x1);  // bit 0 will set to C
  
  TEST_ASSERT_EQUAL_INT8(2, srl_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0xAD) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(1, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_srl_longmem(void){
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XBB, 0x11, 0x01};
  MEM_WRITE_BYTE( 0x1101,  value);
  
  TEST_ASSERT_EQUAL_INT8(4, srl_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0x1101) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_x(void){
  SET_X(0x102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(1, srl_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C);  
}

void test_srl_shortoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 , value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, srl_shortoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_longoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3C22 , value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, srl_longoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_y(void){
  SET_Y(0X102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(2, srl_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_shortoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, srl_shortoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_longoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3C22 ,  value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, srl_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}


void test_srl_shortoff_sp(void){
  SET_SP(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, srl_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C);  
}

void test_srl_shortptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(3, srl_shortptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_longptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(4, srl_longptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_shortptr_w_x(void){ 
  SET_X(0X11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, srl_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_longptr_w_x(void){ 
  SET_X(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , value);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, srl_longptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0xAACC) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_srl_shortptr_w_y(void){
   
  SET_Y(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, srl_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x53, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

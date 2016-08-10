#include "unity.h"
#include "SRA.h"
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
                bit 7 is set to C, then shift left one time
        0x4C    0110  1100
  
         C = 1
  */
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_sra_a(void){
  A = value;
  N = 1;
  Z = 1;
  C = 0;
  uint8_t instr[] = {0XAB};
  
  TEST_ASSERT_EQUAL_INT8(1, sra_a(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, A); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_shortmem(void){

  N = 1;
  Z = 0;
  uint8_t instr[] = {0XBB, 0xAD};
  MEM_WRITE_BYTE( 0xAD,  0);
  
  TEST_ASSERT_EQUAL_INT8(2, sra_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0xAD) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(1, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}


/**
        0x66    0110  0110    
                bit 7 is set to C, then shift left one time
        0xCC    1100  1100
  
         C = 0 , N = 1
*/

void test_sra_longmem(void){
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XBB, 0x11, 0x01};
  MEM_WRITE_BYTE( 0x1101,  0x66);
  
  TEST_ASSERT_EQUAL_INT8(4, sra_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0xCC, MEM_READ_BYTE(0x1101) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_sra_x(void){
  SET_X(0x102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(1, sra_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C);  
}

void test_sra_shortoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 , value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, sra_shortoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_longoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3C22 , value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, sra_longoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_y(void){
  SET_Y(0X102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(2, sra_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_shortoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, sra_shortoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_longoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3C22 ,  value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, sra_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}


void test_sra_shortoff_sp(void){
  SET_SP(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, sra_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C);  
}

void test_sra_shortptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(3, sra_shortptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_longptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(4, sra_longptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_shortptr_w_x(void){ 
  SET_X(0X11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, sra_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_longptr_w_x(void){ 
  SET_X(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , value);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, sra_longptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0xAACC) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_sra_shortptr_w_y(void){
   
  SET_Y(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, sra_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0x4C, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

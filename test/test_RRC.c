#include "unity.h"
#include "RRC.h"
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
  
  value = 0x69;
  
  /**
        0x69    0110  1001    
                bit 0 is set to C, then rotate right , C will assign to bit7, so a right rotation is done
        0xB4    1011  0100
  
         C = 1 , N = 1
  */
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void test_rrc_a(void){
  A = value;
  N = 1;
  Z = 1;
  C = 0;
  uint8_t instr[] = {0XAB};

  TEST_ASSERT_EQUAL_INT8(1, rrc_a(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, A); 
  TEST_ASSERT_EQUAL_INT8(1, N); 
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C);  
}

void test_rrc_shortmem(void){

  N = 1;
  Z = 0;
  C = 1;
  uint8_t instr[] = {0XBB, 0xAD};
  MEM_WRITE_BYTE( 0xAD,  0x0);  
  
  TEST_ASSERT_EQUAL_INT8(2, rrc_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0xAD) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(1, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

  /**
        0x68    0110  1000    
                bit 0 is set to C, then rotate right , C will assign to bit7, so a right rotation is done
        0x34    0011  0100
  
         C = 0 , N = 0
  */
void test_rrc_longmem(void){
  N = 1;
  Z = 1;
  C = 1;
  uint8_t instr[] = {0XBB, 0x11, 0x01};
  MEM_WRITE_BYTE( 0x1101,  0x68);
  
  TEST_ASSERT_EQUAL_INT8(4, rrc_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(0x34, MEM_READ_BYTE(0x1101) ); 
  TEST_ASSERT_EQUAL_INT8(0, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, C); 
}

void test_rrc_x(void){
  SET_X(0x102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(1, rrc_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C);  
}

void test_rrc_shortoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 , value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, rrc_shortoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_longoff_x(void){
  SET_X(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11}; 
  MEM_WRITE_BYTE( 0X3C22 , value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, rrc_longoff_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_y(void){
  SET_Y(0X102B);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB};
  MEM_WRITE_BYTE( 0X102B ,  value);
  
  TEST_ASSERT_EQUAL_INT8(2, rrc_y(instr)); 
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X102B) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_shortoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(3, rrc_shortoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_longoff_y(void){
  SET_Y(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11, 0x11};
  MEM_WRITE_BYTE( 0X3C22 ,  value);  //0x2B11 + 0X1111 = 0X3c22
  
  TEST_ASSERT_EQUAL_INT8(4, rrc_longoff_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X3C22) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}


void test_rrc_shortoff_sp(void){
  SET_SP(0x2B11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X11};
  MEM_WRITE_BYTE( 0X2B22 ,  value);  //0x2B11 + 0X11 = 0X2B22
  
  TEST_ASSERT_EQUAL_INT8(2, rrc_shortoff_sp(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0X2B22) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C);  
}

void test_rrc_shortptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  
  MEM_WRITE_BYTE( 0X13 , 0xAA);  
  MEM_WRITE_BYTE( 0X14 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(3, rrc_shortptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_longptr_w(void){ 
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X15};
  MEM_WRITE_BYTE( 0X1315 , 0xAA);  
  MEM_WRITE_BYTE( 0X1316 , 0xBB);  
  MEM_WRITE_BYTE( 0xAABB , value);  
  
  TEST_ASSERT_EQUAL_INT8(4, rrc_longptr_w(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0xAABB) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_shortptr_w_x(void){ 
  SET_X(0X11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, rrc_shortptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_longptr_w_x(void){ 
  SET_X(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13, 0X00};
  MEM_WRITE_BYTE( 0X1300 , 0xAA);  
  MEM_WRITE_BYTE( 0X1301 , 0xBB);  
  MEM_WRITE_BYTE( 0xAACC , value);  // 0XAABB + 0X11 = 0XAACC
  
  TEST_ASSERT_EQUAL_INT8(4, rrc_longptr_w_x(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0xAACC) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

void test_rrc_shortptr_w_y(void){
   
  SET_Y(0x11);
  N = 1;
  Z = 1;
  uint8_t instr[] = {0XFB, 0X13};  
  MEM_WRITE_BYTE( 0X13 , 0x11);  
  MEM_WRITE_BYTE( 0X14 , 0x11);  
  MEM_WRITE_BYTE( 0x1122 , value);  // 0X1111 + 0X11 = 0X1122
  
  TEST_ASSERT_EQUAL_INT8(3, rrc_shortptr_w_y(instr));
  TEST_ASSERT_EQUAL_INT8(0xB4, MEM_READ_BYTE(0x1122) ); 
  TEST_ASSERT_EQUAL_INT8(1, N);  
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(1, C); 
}

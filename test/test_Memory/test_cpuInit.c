#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include "MCU_Operation.h"
#include "Description.h"
#include "CException.h"
#include "ErrorObject.h"

void setUp(void)
{                          
}

void tearDown(void)
{
  free(cpu);
  free(cpuBlock);
}

/*
struct CPU_t{
  uint8_t   a;    // 0x7F00
  uint8_t   pce;  
  uint8_t   pch;     
  uint8_t   pcl;   
  uint8_t   xh;    
  uint8_t   xl;  
  uint8_t   yh;  
  uint8_t   yl;   
  uint8_t  sph; 
  uint8_t  spl; 
  Flag     ccr;   // 0x7F0A 
};



*/
void test_cpuInit_given_write_something_to_CPU_should_save_in_cpuBlock_data_because_is_pointed(void)
{ 
  cpuInit(CPU_START_ADDR, CPU_SIZE); 
  
  uint8_t *dataArr = cpuBlock->data;
  
  A = 0xAA;
  SET_PC(0x112233);
  SET_X(0xCCDD);
  SET_Y(0xEEFF);
  SET_SP(0x77BB);
  CC = 0x99;

  TEST_ASSERT_EQUAL_INT8(0xAA, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0x11, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0x22, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0x33, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0xCC, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0xDD, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0xEE, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0xFF, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0x77, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0xBB, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0x99, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0, *dataArr++);
  TEST_ASSERT_EQUAL_INT8(0, *dataArr++);
}



#include "unity.h"
#include "MOV.h"
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

/**

    MOV $1234,#$12            M(longmem) ← imm.b
    
    MOV $12,$34               M(mem1.b) ← M(mem2.b)
    MOV mem1,mem2

    MOV $1234,$5678         M(mem1.w) ← M(mem2.w)
    MOV mem1,mem2
*/



void test_mov_longmem_byte(void){
  uint8_t byte = 0x77;
  uint16_t longmem = 0x1122;
  
  uint8_t instr[] = {0XAB, byte, 0x11, 0x22}; // XX , MS  ,LS
  
  TEST_ASSERT_EQUAL_INT8(4, mov_longmem_byte(instr));
  TEST_ASSERT_EQUAL_INT8(byte, MEM_READ_BYTE(longmem));
}


void test_mov_shortmem_shortmem(void){
  uint8_t byte = 0x77;
  uint8_t shortmem2   = 0xAD;
  uint8_t shortmem1   = 0xBB;
  
  MEM_WRITE_BYTE(shortmem2,byte); 
  
  uint8_t instr[] = {0XBB, shortmem2, shortmem1}; // XX2 , XX1
  
  TEST_ASSERT_EQUAL_INT8(3, mov_shortmem_shortmem(instr));
  TEST_ASSERT_EQUAL_INT8(byte, MEM_READ_BYTE(shortmem1));
}



void test_mov_longmem_longmem(void){
  uint8_t byte = 0x76;
  uint16_t longmem2   = 0x2233;
  uint16_t longmem1   = 0x4455;

  MEM_WRITE_BYTE(longmem2,byte);

  uint8_t instr[] = {0XBB, 0x22, 0x33, 0x44 , 0x55 };  // MS2, LS2 , MS1, LS1
  
  TEST_ASSERT_EQUAL_INT8(5, mov_longmem_longmem(instr));
  TEST_ASSERT_EQUAL_INT8(byte, MEM_READ_BYTE(longmem1));
}
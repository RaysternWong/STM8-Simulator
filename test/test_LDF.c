#include "unity.h"
#include "LDF.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>

uint8_t value, msbMem, lsbMem;
uint16_t longMem;
void setUp(void){
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
  gpioInit(0x0, 0x01FFFF);
  msbMem = 0x33;
  lsbMem = 0x44;
  longMem = 0x3344;

  value = 0x22;
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

//----------------------------test load byte to A-----------------------

void test_ldf_a_extmem(void){
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};

  MEM_WRITE_BYTE( 0x012233 ,  value); 
   
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_extmem(instr));
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N); 
}

void test_ldf_a_extoff_x(void){
  SET_X(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  MEM_WRITE_BYTE( 0X012244 ,  value);   // 0X012233 + 0x11 = 0X012244
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_extoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_extoff_y(void){
  SET_Y(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  MEM_WRITE_BYTE( 0X012244 ,  value);   // 0X012233 + 0x11 = 0X012244
  
  TEST_ASSERT_EQUAL_INT8( 5, ldf_a_extoff_y(instr));
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_longptr_e_x(void){
  SET_X(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;

  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  MEM_WRITE_BYTE( 0x01eebb , value); 
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_longptr_e_x(instr));
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_longptr_e_y(void){
  SET_Y(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  MEM_WRITE_BYTE( 0x01eebb , value); 
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_longptr_e_y(instr));
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_longptr_e(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;

  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  MEM_WRITE_BYTE( 0x01eeaa , value); 
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_longptr_e(instr));
  TEST_ASSERT_EQUAL_INT8( value, A);
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

//----------------------------test load A to mem storage-----------------------

void test_ldf_a_to_extmem(void){
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  A = value;
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_to_extmem(instr));
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0x012233));
}

void test_ldf_a_to_extoff_x(void){
  SET_X(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  A = value;
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_to_extoff_x(instr)); 
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0X012244));
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_to_extoff_y(void){
  SET_Y(0x11);
  uint8_t instr[] = { 0xAB, 0x01,0x22,0x33};
  A = value;
  
  TEST_ASSERT_EQUAL_INT8( 5, ldf_a_to_extoff_y(instr));
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0X012244));
}

void test_ldf_a_to_longptr_e_x(void){
  SET_X(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;

  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  A = value;
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_to_longptr_e_x(instr));
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0x01eebb));
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_to_longptr_e_y(void){
  SET_Y(0x11);
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;
  
  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  A = value;
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_to_longptr_e_y(instr));
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0x01eebb));
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

void test_ldf_a_to_longptr_e(void){
  uint8_t instr[] = {0XBB, msbMem, lsbMem};
  uint16_t longMem1 = longMem + 1;
  uint16_t longMem2 = longMem + 2;

  MEM_WRITE_BYTE( longMem  , 0x01);
  MEM_WRITE_BYTE( longMem1 , 0xee);
  MEM_WRITE_BYTE( longMem2 , 0xaa);
  A = value;
  
  TEST_ASSERT_EQUAL_INT8( 4, ldf_a_to_longptr_e(instr));
  TEST_ASSERT_EQUAL_INT8( value, MEM_READ_BYTE(0x01eeaa));
  TEST_ASSERT_EQUAL_INT8(0, Z); 
  TEST_ASSERT_EQUAL_INT8(0, N);
}

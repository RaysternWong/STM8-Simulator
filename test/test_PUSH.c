#include "unity.h"
#include "PUSH.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

/**  Please refer all the definations and marco in MCU_Operation.h
*/ 

uint16_t inputSP;
uint8_t  value;

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(RAM_START_ADDR, 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
  
  // Tests Variable share to all tests
  value = 0xAA;
  inputSP = 0x1234;
  SET_SP(inputSP);

}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);
}

// This function is in mcu_operation.c, because is has sharing's use 
void test_mcu_push(void)
{
  mcu_push(value);
  TEST_ASSERT_EQUAL_INT8(value, MEM_READ_BYTE(inputSP) ); //test is the value has pushed into the address, which hold by SP
  TEST_ASSERT_EQUAL_INT8( --inputSP, SP );                // test is decrement of SP 
}

void test_push_a(void)
{
  A = 0x11;
  uint8_t instr[] = {0XAB};
  
  uint8_t length = push_a(instr);
  TEST_ASSERT_EQUAL_INT8(A, MEM_READ_BYTE(inputSP) );  //test is A has pushed into the address, which hold by SP
  TEST_ASSERT_EQUAL_INT8( --inputSP, SP );
  TEST_ASSERT_EQUAL_INT8( 1, length );    
}

void test_push_cc(void)
{
  CC = 0x11;
  uint8_t instr[] = {0XAB};
  
  uint8_t length = push_cc(instr);
  TEST_ASSERT_EQUAL_INT8(CC, MEM_READ_BYTE(inputSP) );  //test is CC has pushed into the address, which hold by SP
  TEST_ASSERT_EQUAL_INT8( --inputSP, SP );   
  TEST_ASSERT_EQUAL_INT8( 1, length );  
}

void test_push_byte(void)
{
  uint8_t instr[] = {0XAB, value};
  
  uint8_t length = push_byte(instr);
  TEST_ASSERT_EQUAL_INT8(value, MEM_READ_BYTE(inputSP) );  //test is value has pushed into the address, which hold by SP
  TEST_ASSERT_EQUAL_INT8( --inputSP, SP );   
  TEST_ASSERT_EQUAL_INT8( 2, length );   
}

void test_push_longmem(void)
{
  uint8_t memMSB = 0xAA, memLSB = 0xBB;
  uint16_t longmem = 0xAABB;
  MEM_WRITE_BYTE(longmem, value);
  
  uint8_t instr[] = {0XAB, memMSB, memLSB};
  
  uint8_t length = push_longmem(instr);
  TEST_ASSERT_EQUAL_INT8(value, MEM_READ_BYTE(inputSP) );  //test is value hold by longmem has pushed into the address
  TEST_ASSERT_EQUAL_INT8( --inputSP, SP );   
  TEST_ASSERT_EQUAL_INT8( 3, length );  
}
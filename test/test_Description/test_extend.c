#include "unity.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to 27FFFF, for testing purpose (FFFF / 100 = FF)
  ramBlock = createMemoryBlock(0x0000 , 0x17FFFF);
  setMemoryTable( ramMemory , 0 , 0x17FFFF); 

}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

// return the address of longPtrE
void test_getLongE(void)
{
  uint8_t memMSB = 0xAA, memLSB = 0xBB;
  uint16_t longmem = 0xAABB;
  uint16_t longmem_plus1 = longmem + 1;
  uint16_t longmem_plus2 = longmem + 2;

  MEM_WRITE_BYTE(longmem, 0x12);
  MEM_WRITE_BYTE(longmem_plus1, 0x34);
  MEM_WRITE_BYTE(longmem_plus2, 0x56);

  
  uint8_t instr[] = {0XAB, memMSB, memLSB}; 
  
  uint32_t address = getLongE( instr );
  TEST_ASSERT_EQUAL_INT32( 0x123456 , address ); 
}


// return the value of address of longPtrE
void test_getLongPtrE(void)
{
  uint8_t value = 0x33, memMSB = 0xAA, memLSB = 0xBB;
  uint16_t longmem = 0xAABB;
  uint16_t longmem_plus1 = longmem + 1;
  uint16_t longmem_plus2 = longmem + 2;

  MEM_WRITE_BYTE(longmem, 0x12);
  MEM_WRITE_BYTE(longmem_plus1, 0x34);
  MEM_WRITE_BYTE(longmem_plus2, 0x56);

  MEM_WRITE_BYTE(0x123456, value);
  uint8_t instr[] = {0XAB, memMSB, memLSB}; 
  
  uint8_t longPtrE = getLongPtrE( instr );
  TEST_ASSERT_EQUAL_INT8( value , longPtrE ); 
}
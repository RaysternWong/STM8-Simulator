#include "unity.h"
#include "CALLF.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

//Please refer all the definations and marco in MCU_Operation.h

/**
CALLF $123456
                  PC ← PC+4
                  M(SP--) ← PCL
                  M(SP--) ← PCH
                  M(SP--) ← PCE
                  PC ← extmem
*/

uint8_t value;

uint16_t inputSP, sp_minus1, sp_minus2, sp_minus3;

void setUp(void)
{
  instantiateCPU();
  
  // Set the ramMemory occupy the memoryTable from 0000 to 11FFFF, for testing purpose 
  ramBlock = createMemoryBlock(0x0000 , 0x11FFFF);
  setMemoryTable( ramMemory , 0 , 0x11FFFF); 

  inputSP = 0x1122;
  sp_minus1 = inputSP - 1;
  sp_minus2 = inputSP - 2;
  sp_minus3 = inputSP - 3;
  SET_SP(inputSP);
  
  PCH = 0x33;
  PCL = 0x44;
  
  value = 0xEE;
}

void tearDown(void)
{
  free(cpu);
  free(ramBlock);  
}

void test_mcu_callf(void){
  
  uint32_t address = 0x112233;
  uint8_t length = 4;
  mcu_callf( address,  length);
  
  TEST_ASSERT_EQUAL_INT32(address, PC);
  TEST_ASSERT_EQUAL_INT8(sp_minus3, SP);
}

void test_callf_extmem(void){
  
  uint8_t memEXT = 0x11, memMSB = 0xAA, memLSB = 0xBB;
  uint32_t extmem = 0x11AABB;

  uint8_t instr[] = {0XAB, memEXT, memMSB, memLSB}; 
  
  uint8_t length = callf_extmem(instr);
  TEST_ASSERT_EQUAL_INT32( extmem , PC );   
  TEST_ASSERT_EQUAL_INT8( 4, length );  
}

void test_callf_longptr_e(void){
  
  uint8_t memMSB = 0xAA, memLSB = 0xBB;
  uint16_t extmem = 0xAABB;
  uint16_t msbmem = extmem + 1;
  uint16_t lsbmem = msbmem + 1;

  MEM_WRITE_BYTE(extmem,0x11);
  MEM_WRITE_BYTE(msbmem,0x44);
  MEM_WRITE_BYTE(lsbmem,0x77);


  uint8_t instr[] = {0XAB, memMSB, memLSB}; 
  
  uint8_t length = callf_longptr_e(instr);
  TEST_ASSERT_EQUAL_INT32( 0x114477 , PC );   
  TEST_ASSERT_EQUAL_INT8( 4, length );  
}
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
                            // 0x00          0x027FFF
  setMemoryTable(noMemory, STM8_START_ADDR, STM8_END_ADDR );
}

void tearDown(void)
{
  
}

/**
*     Ram address range
*
*     0x00 0000  ----------->  0x00 03FF
*
*
*
*/

void test_ramInit_given_write_a_data_to_a_address_is_within_ram_address_range(void)
{ 
  ramInit();
  MEM_WRITE_BYTE(0x222, 0xAA );
  
  TEST_ASSERT_EQUAL_INT8(0xAA, RAM_ARR(0x222));
  TEST_ASSERT_EQUAL_INT8(0xAA, MEM_READ_BYTE(0x222));
  
  free(ramBlock);
}

void test_ramInit_given_write_a_data_to_a_address_is_without_ram_address_range(void)
{
  ErrorObject* err;
  
  ramInit();
 
  Try{
    MEM_WRITE_BYTE(0x400, 0xAA );
    TEST_FAIL_MESSAGE("Expected ERR_UNINITIALIZED_ADDRESS but no error were thrown");
  }Catch(err){
    TEST_ASSERT_EQUAL(ERR_UNINITIALIZED_ADDRESS, err->errorCode);
    TEST_ASSERT_EQUAL_STRING( "Access uninitialized memory from Type: MEM_READ Address: 400\t Size 0\n", err->errorMsg);
  }
  free(ramBlock);
  freeError(err);
}

void test_ramInit_given_read_a_data_from_a_address_is_without_ram_address_range(void)
{
  ErrorObject* err;
  
  ramInit();
 
  Try{
    MEM_READ_BYTE(0x400);
    TEST_FAIL_MESSAGE("Expected ERR_UNINITIALIZED_ADDRESS but no error were thrown");
  }Catch(err){
    TEST_ASSERT_EQUAL(ERR_UNINITIALIZED_ADDRESS, err->errorCode);
    TEST_ASSERT_EQUAL_STRING( "Access uninitialized memory from Type: MEM_READ Address: 400\t", err->errorMsg);
  }
  free(ramBlock);
  freeError(err);
}



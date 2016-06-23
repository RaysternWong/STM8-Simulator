#include "unity.h"
#include "ADD.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define A   cpu.accA       //Accumulator
#define X   cpu.index_X    //Index registers X  

void setUp(void)
{

}

void tearDown(void)
{
}



// 0x01 + 0x05 = 0x06
void test_add_a_ht_byte_with_offset_5_should_return_2(void)
{
  A = 0x01;
  uint8_t instr[] = {0XAB, 0X05};
  
  int ans = add_a_ht_byte(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x06, A);
  TEST_ASSERT_EQUAL(2, ans);
}

void test_add_a_shortoff_x_with_offset_5_should_return_2(void)
{
  A = 0x01;
  X = 0x100;
 
  uint8_t instr[] = {0XEB, 0X05};
  
  // int ans = add_a_shortmem(instr);
  
  // TEST_ASSERT_EQUAL_INT8(0x06, A);
  // TEST_ASSERT_EQUAL(2, ans);
}
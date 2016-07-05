#include "unity.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


void setUp(void)
{

}

void tearDown(void)
{

}

/**
*     uint16_t combineMostLeastByte(uint8_t mostByte, uint8_t leastByte)
*
*/ 

void test_combineMostLeastByte_given_mostByte_is_0x24_leastByte_is_0x31_should_return_0x2341(void){
  
  uint8_t mostByte  = 0x24;
  uint8_t leastByte = 0x31;
  
  uint16_t fullByte = combineMostLeastByte(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0x2431, fullByte);
}

// -0x7f = 0x81
void test_combineMostLeastByte_given_mostByte_is_neg_0x7f_leastByte_is_0xab_should_return_0x81ab(void){
  
  uint8_t mostByte  = -0x7f;
  uint8_t leastByte = 0xab;
  
  uint16_t fullByte = combineMostLeastByte(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0x81ab, fullByte);
}


 // -0x34 = 0xcc , -0x21 = 0xdf
void test_combineMostLeastByte_given_mostByte_is_neg_0x34_leastByte_is_neg_0x21_should_return_0xccdf(void){
  
  uint8_t mostByte  = -0x34;
  uint8_t leastByte = -0x21;
  
  uint16_t fullByte = combineMostLeastByte(mostByte, leastByte);
  
  TEST_ASSERT_EQUAL_INT16(0xccdf, fullByte);
}

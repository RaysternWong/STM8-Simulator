#include "unity.h"
#include "ADD.h"
#include <stdint.h>
#include "CPUConfig.h"

#define A   cpu.accA //Accumulator

void setUp(void)
{

}

void tearDown(void)
{
}



// 0x01 + 0x05 = 0x06
void test_add_a_ht_byte_with_offset_5(void)
{
  uint8_t instr[] = {0XAB, 0X05};
  

  
  
}
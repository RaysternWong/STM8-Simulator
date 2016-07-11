#include "unity.h"
#include "MUL.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>


/**

MUL X,A         X ← X*A  
MUL Y,A         Y ← Y*A

Multiplies the 8-bit value in index register, low byte, (XL or YL) by the 8-bit
value in the accumulator to obtain a 16-bit unsigned result in the index
register. After the operation, index register contains the 16-bit result. The
accumulator remains unchanged. The initial value of the high byte of the
index register (XH or YH) is ignored.



*/

void setUp(void)
{
  instantiateCPU();
  ramBlock = createMemoryBlock(0x0000 , 0xFFFF);
  setMemoryTable( ramMemory , 0 , 0xFFFF); 
}

void tearDown(void)
{
   free(cpu);
   free(ramBlock);
}


void test_mul_x_a(void)
{
	SET_X(0x1234);
  A = 0xcc;
  
  
  uint16_t result = XL * A;  //0x34 * 0xcc = 0x2970
  
  uint8_t instr[]  = {0XBB};
  
  uint8_t length = mul_x_a(instr);
  TEST_ASSERT_EQUAL_INT8(1, length);
  TEST_ASSERT_EQUAL_INT16(result, X); // is X updated
  TEST_ASSERT_EQUAL_INT16(0xcc, A);   // iz A remain unchanged
}

void test_mul_y_a(void)
{
	SET_Y(0x1234);
  A = 0xcc;
  
  uint16_t result = YL * A;  //0x34 * 0xcc = 0x2970
  
  uint8_t instr[]  = {0XBB};
  
  uint8_t length = mul_y_a(instr);
  TEST_ASSERT_EQUAL_INT8(1, length);
  TEST_ASSERT_EQUAL_INT16(result, Y); // is X updated
  TEST_ASSERT_EQUAL_INT16(0xcc, A);   // iz A remain unchanged
}


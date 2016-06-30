#include "unity.h"
#include "ADDW.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <malloc.h>

#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)


void setUp(void)
{
  instantiateCPU();
}

void tearDown(void)
{
   free(cpu);
}


/**     0x 13 67
*   +   0x 22 11
*----------------
*       0x 35 78
*---------------
*/
void test_addw_x_word(void)
{
  XH = 0x13;
  XL = 0x67;
  
  uint8_t instr[] = {0XAB, 0X22, 0X11};
  
  int length = addw_x_word(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x35, XH);
  TEST_ASSERT_EQUAL_INT8(0x78, XL);
  TEST_ASSERT_EQUAL(3, length);
}

/**     0x 13 67
*   +   0x 22 FF
*----------------
*       0x 36 66
*---------------
*/
void test_addw_x_word_with_carry_from_bit8_to_bit9(void)
{
  XH = 0x13;
  XL = 0x67;
  
  uint8_t instr[] = {0XAB, 0X22, 0XFF};
  
  int length = addw_x_word(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x36, XH);
  TEST_ASSERT_EQUAL_INT8(0x66, XL);
  TEST_ASSERT_EQUAL(3, length);
}

/**     0x 13 67
*   +   0x    02
*----------------
*       0x 13 69
*---------------
*/
void test_add_x_longmem(void)
{
  XH = 0x13;
  XL = 0x67;
  
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  
  writeValueToTheAddress( 0x1101,  0x02);
  
  int length = addw_x_longmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x13, XH);
  TEST_ASSERT_EQUAL_INT8(0x69, XL);
  TEST_ASSERT_EQUAL(4, length);
}

/**     0x 13 67
*   +   0x    02
*----------------
*       0x 13 69
*---------------
*/
void test_addw_x_shortoff_sp(void)
{
  XH = 0x13;
  XL = 0x67;
  
  SPH = 0X2B;
  SPL = 0X11;
  
  uint8_t addr = 0x11;

  
  uint8_t instr[] = {0XBB, addr};
  
  writeValueToTheAddress( 0x2B22,  0x02);  //2B11 + 11 = 2B22
  
  int length = addw_x_shortoff_sp(instr);
  TEST_ASSERT_EQUAL_INT8(0x13, XH);
  TEST_ASSERT_EQUAL_INT8(0x69, XL);
  TEST_ASSERT_EQUAL(3, length);
}

/**     0x 13 67
*   +   0x 22 FF
*----------------
*       0x 36 66
*---------------
*/
void test_addw_y_word_with_carry_from_bit8_to_bit9(void)
{
  YH = 0x13;
  YL = 0x67;
  
  uint8_t instr[] = {0XAB, 0X22, 0XFF};
  
  int length = addw_y_word(instr);
  
  TEST_ASSERT_EQUAL_INT8(0x36, YH);
  TEST_ASSERT_EQUAL_INT8(0x66, YL);
  TEST_ASSERT_EQUAL(4, length);
}

/**     0x 13 67
*   +   0x    02
*----------------
*       0x 13 69
*---------------
*/
void test_add_y_longmem(void)
{
  YH = 0x13;
  YL = 0x67;
  
  uint8_t addrMSB = 0x11;
  uint8_t addrLSB = 0x01;
  
  uint8_t instr[] = {0XBB, addrMSB, addrLSB};
  
  writeValueToTheAddress( 0x1101,  0x02);
  
  int length = addw_y_longmem(instr);
  TEST_ASSERT_EQUAL_INT8(0x13, YH);
  TEST_ASSERT_EQUAL_INT8(0x69, YL);
  TEST_ASSERT_EQUAL(4, length);
}

/**     0x 13 67
*   +   0x    02
*----------------
*       0x 13 69
*---------------
*/
void test_addw_y_shortoff_sp(void)
{
  YH = 0x13;
  YL = 0x67;
  
  SPH = 0X2B;
  SPL = 0X11;
  
  uint8_t addr = 0x11;

  
  uint8_t instr[] = {0XBB, addr};
  
  writeValueToTheAddress( 0x2B22,  0x02);  //2B11 + 11 = 2B22
  
  int length = addw_y_shortoff_sp(instr);
  TEST_ASSERT_EQUAL_INT8(0x13, YH);
  TEST_ASSERT_EQUAL_INT8(0x69, YL);
  TEST_ASSERT_EQUAL(3, length);
}

/**     0x 11 25
*   +   0x    FF
*----------------
*       0x 12 24
*---------------
*/
void test_addw_sp_byte(void)
{
  SPH = 0X11;
  SPL = 0X25;
  
  uint8_t byte = 0xFF;

  uint8_t instr[] = {0XBB, byte};
  
  int length = addw_sp_byte(instr);
  TEST_ASSERT_EQUAL_INT8(0x12, SPH);
  TEST_ASSERT_EQUAL_INT8(0x24, SPL);
  TEST_ASSERT_EQUAL(2, length);
}
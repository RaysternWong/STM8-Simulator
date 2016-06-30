#include "unity.h"
#include "DIVW.h"
#include "MCU_Operation.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include <malloc.h>
#include "ErrorCode.h"
#include "CException.h"


#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)

#define V   (cpu->ccr).bits.v   //overFlow
#define L1  (cpu->ccr).bits.l1  //interrupt mask level 1
#define H   (cpu->ccr).bits.h   //half cary
#define L0  (cpu->ccr).bits.l0  //interrupt mask level 0
#define N   (cpu->ccr).bits.n   //negative
#define Z   (cpu->ccr).bits.z   //zero
#define C   (cpu->ccr).bits.c   //carry



void setUp(void)
{
  instantiateCPU();
  clearConditionCodeRegister(&(cpu->ccr));
}

void tearDown(void)
{
  free(cpu);
}

/**
*   X = 0X3333;
*   Y = 0X1111;
*   
*   quotient = 0X3333 /0X1111 = 0x03
*   remainder = 0X3333 /0x11 = 0;
*
*  X = quotient
*  A = remainder
*/
void test_div_x_y(void)
{
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X11;
  YL = 0X11;
    
  int length = div_x_y();
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x03, XL);
  TEST_ASSERT_EQUAL_INT8(0x00, YH);
  TEST_ASSERT_EQUAL_INT8(0x00, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

/**
*   X = 0X3333;
*   Y = 0X2222;
*   
*   quotient = 0X3333 /0X1111 = 0x01
*   remainder = 0X3333 /0x2222 = 0x1111;
*
*  X = quotient
*  A = remainder
*/
void test_div_x_y_with_remaidner(void)
{
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X22;
  YL = 0X22;
    
  int length = div_x_y();
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x01, XL);
  TEST_ASSERT_EQUAL_INT8(0x11, YH);
  TEST_ASSERT_EQUAL_INT8(0x11, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(0, C);
}

void test_div_x_y_with_x_equal_0(void)
{
  XH = 0X00;
  XL = 0X00;
  
  YH = 0X22;
  YL = 0X22;
    
  int length = div_x_y();
  TEST_ASSERT_EQUAL_INT16(0x00, XH);
  TEST_ASSERT_EQUAL_INT16(0x00, XL);
  TEST_ASSERT_EQUAL_INT8(0x00, YH);
  TEST_ASSERT_EQUAL_INT8(0x00, YL);
  
  TEST_ASSERT_EQUAL(1, length);
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(1, Z);
  TEST_ASSERT_EQUAL(0, C);
}

void test_div_x_y_with_y_equal_0_should_set_C_and_get_error(void)
{
  CEXCEPTION_T err;
  XH = 0X33;
  XL = 0X33;
  
  YH = 0X00;
  YL = 0X00;
  
  Try{
    int length = div_x_y();
    TEST_FAIL_MESSAGE("Expected ERR_DIVIDER_IS_0");
    
  TEST_ASSERT_EQUAL(1, length);

    
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_DIVIDER_IS_0, err, "Expected ERR_DIVIDER_IS_0");
  }
  
  TEST_ASSERT_EQUAL(0, V);
  TEST_ASSERT_EQUAL(0, L1);
  TEST_ASSERT_EQUAL(0, H);
  TEST_ASSERT_EQUAL(0, L0);
  TEST_ASSERT_EQUAL(0, N);
  TEST_ASSERT_EQUAL(0, Z);
  TEST_ASSERT_EQUAL(1, C);
}


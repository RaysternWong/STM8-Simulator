#include "DIV.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorCode.h"

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

void mcu_div(uint8_t *mostByte, uint8_t *leastByte)
{
  if( A == 0){
    C = 1;
    Throw(ERR_DIVIDER_IS_0);
  }
 
  uint16_t regXY      = combineMostLeastByte(*mostByte, *leastByte);
  uint16_t quotient   = regXY / A;
  uint8_t  remainder  = regXY % A;
  
  N = 0;
  Z = (quotient == 0 ? 1 : 0);
  H = 0;
  V = 0;
  
  A = remainder;
  initMostLeastByte( mostByte, leastByte, quotient);
}

uint8_t div_x_a(void)
{
  mcu_div(&XH, &XL);
  return 1;
}

uint8_t div_y_a(void)
{
  mcu_div(&YH, &YL);
  return 2;
}
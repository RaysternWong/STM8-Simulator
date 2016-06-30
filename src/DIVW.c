#include "DIVW.h"
#include <stdint.h>
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "ErrorCode.h"

#define A     (cpu->a)           //Accumulator
#define XH    (cpu->xh)           //most significant byte of the X index register  (1 byte)
#define XL    (cpu->xl)           //least significant byte of the X index register (1 byte)
#define YH    (cpu->yh)           //most significant byte of the y index register  (1 byte)
#define YL    (cpu->yl)           //least significant byte of the y index register (1 byte)
#define SPH   (cpu->sph)          //most significant byte of the sph index register  (1 byte)
#define SPL   (cpu->spl)          //least significant byte of the spl index register (1 byte)

#define V   ((cpu->ccr).bits.v)   //overFlow
#define L1  ((cpu->ccr).bits.l1)  //interrupt mask level 1
#define H   ((cpu->ccr).bits.h)   //half cary
#define L0  ((cpu->ccr).bits.l0)  //interrupt mask level 0
#define N   ((cpu->ccr).bits.n)   //negative
#define Z   ((cpu->ccr).bits.z)   //zero
#define C   ((cpu->ccr).bits.c)   //cary

uint8_t div_x_y(void)
{
  uint16_t x      = combineMostLeastByte(XH, XL);
  uint16_t y      = combineMostLeastByte(YH, YL);
  
  if( y == 0){
    C = 1;
    Throw(ERR_DIVIDER_IS_0);
  }
  
  uint16_t quotient   = x / y;
  uint16_t remainder  = x % y;
  
  N = 0;
  Z = (quotient == 0 ? 1 : 0);
  H = 0;
  V = 0;
  
  initMostLeastByte( &XH, &XL, quotient);
  initMostLeastByte( &YH, &YL, remainder);
  
  return 1;
}
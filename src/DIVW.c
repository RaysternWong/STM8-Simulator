#include "DIVW.h"
#include <stdint.h>
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "ErrorObject.h"

uint8_t div_x_y(uint8_t *opcode)
{
  uint16_t x = X, y = Y;
  
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
  
  SET_X(quotient);
  SET_Y(remainder);
  // initMostLeastByte( &XH, &XL, quotient);
  // initMostLeastByte( &YH, &YL, remainder);
  
  return 1;
}
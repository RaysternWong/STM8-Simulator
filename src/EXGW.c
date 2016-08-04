#include "EXGW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t exgw_x_y(uint8_t *opcode){
  uint16_t temp = X;
  SET_X(Y);
  SET_Y(temp);
  return 1;  
}
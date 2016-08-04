#include "CLRW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t clrw_x(uint8_t *opcode){
  SET_X(0);
  N = 0;
  Z = 1;
  return 1;
}

uint8_t clrw_y(uint8_t *opcode){
  SET_Y(0);
  N = 0;
  Z = 1;
  return 2;  
}
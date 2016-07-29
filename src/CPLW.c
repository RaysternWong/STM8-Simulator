#include "CPLW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t cplw_x(uint8_t *opcode){
  uint16_t result = 0xFFFF - X;
  SET_X(result);
  SET_Z_N_FLAG_FOR_16_BIT(result);
  C = 1;
  return 1;
}

uint8_t cplw_y(uint8_t *opcode){
  uint16_t result = 0xFFFF - Y;
  SET_Y(result);
  SET_Z_N_FLAG_FOR_16_BIT(result);
  C = 1; 
  return 2;
}
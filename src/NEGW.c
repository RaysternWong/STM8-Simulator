#include "NEGW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t negw_x  (uint8_t *opcode){
  SET_X(0-X);
  uint16_t result = X;
  N = R15;
  Z = ( result == 0 ? 1 : 0 );
  V = ( result == 0x8000 ? 1 : 0 );
  C = ~Z; 
  return 1;
}

uint8_t negw_y  (uint8_t *opcode){
  SET_Y(0-Y); 
  uint16_t result = Y;
  N = R15;
  Z = ( result == 0 ? 1 : 0 );
  V = ( result == 0x8000 ? 1 : 0 );
  C = ~Z; 
  return 2; 
}
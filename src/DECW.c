#include "DECW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t decw_x(uint8_t *opcode){
  uint16_t a = X;
  uint16_t value = 1;
  uint16_t result = a - value;
  
  SET_X(result);
  SET_Z_N_FLAG_FOR_16_BIT(result);
  V = ( A15 & M15 | M15 & _R15 | _R15 & A15 ) ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
  return 1;
}

uint8_t decw_y(uint8_t *opcode){
  uint16_t a = Y;
  uint16_t value = 1;
  uint16_t result = a - value;
  
  SET_Y(result);
  SET_Z_N_FLAG_FOR_16_BIT(result);
  V = ( A15 & M15 | M15 & _R15 | _R15 & A15 ) ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
  return 2;
}
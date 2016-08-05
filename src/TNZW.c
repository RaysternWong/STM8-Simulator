#include "TNZW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t tnzw_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG_FOR_WORD( X );
  return 1;
}

uint8_t tnzw_y(uint8_t *opcode){
  UPDATE_Z_N_FLAG_FOR_WORD( Y );
  return 2;
}
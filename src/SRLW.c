#include "SRLW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t srlw_x(uint8_t *opcode){
  REG_WORD_SHIFT_RIGHT(XH);
  return 1;
}

uint8_t srlw_y(uint8_t *opcode){
  REG_WORD_SHIFT_RIGHT(YH);
  return 2;
}
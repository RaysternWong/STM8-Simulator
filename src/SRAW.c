#include "SRAW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sraw_x(uint8_t *opcode){
  REG_WORD_SHIFT_RIGHT_ARITHMETIC(XH);
  return 1;
}

uint8_t sraw_y(uint8_t *opcode){
  REG_WORD_SHIFT_RIGHT_ARITHMETIC(YH);
  return 2;
}
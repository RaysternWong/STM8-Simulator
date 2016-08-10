#include "SLLW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sllw_x(uint8_t *opcode){
  REG_WORD_SHIFT_LEFT(XH);
  return 1;
}

uint8_t sllw_y(uint8_t *opcode){
  REG_WORD_SHIFT_LEFT(YH);
  return 2;
}
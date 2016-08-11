#include "RRCW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t rrcw_x(uint8_t *opcode){
  REG_WORD_ROTATE_RIGHT(XH);
  return 1;
}

uint8_t rrcw_y(uint8_t *opcode){
  REG_WORD_ROTATE_RIGHT(YH);
  return 2;
}
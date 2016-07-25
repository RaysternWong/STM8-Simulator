#include "NEG.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t neg_a(uint8_t *opcode){
  mcu_neg(A);
  return 1;
}

uint8_t neg_shortmem(uint8_t *opcode){
  mcu_neg(GET_SHORT_MEM(opcode));
  return 2;
}

uint8_t neg_longmem(uint8_t *opcode){
  mcu_neg(GET_LONG_MEM(opcode));
  return 4;
}

uint8_t neg_x(uint8_t *opcode){
  mcu_neg(X);
  return 1;
}

uint8_t neg_shortoff_x(uint8_t *opcode){
  mcu_neg(GET_SHORT_OFF_X(opcode));
  return 2;
}

uint8_t neg_longoff_x(uint8_t *opcode){
  mcu_neg(GET_LONG_OFF_X(opcode));
  return 4;
}

uint8_t neg_y(uint8_t *opcode){
  mcu_neg(Y);
  return 2;
}

uint8_t neg_shortoff_y(uint8_t *opcode){
  mcu_neg(GET_SHORT_OFF_Y(opcode));
  return 3;
}

uint8_t neg_longoff_y(uint8_t *opcode){
  mcu_neg(GET_LONG_OFF_Y(opcode));
  return 4;
}

uint8_t neg_shortoff_sp(uint8_t *opcode){
  mcu_neg(GET_SHORT_OFF_SP(opcode));
  return 2;
}

uint8_t neg_shortptr_w(uint8_t *opcode){
  mcu_neg(GET_SHORT_PTR_W(opcode));
  return 3;
}
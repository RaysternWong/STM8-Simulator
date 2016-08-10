#include "SRL.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t srl_a(uint8_t *opcode){
  REG_SHIFT_RIGHT(A);
  return 1;
}

uint8_t srl_shortmem(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_MEM(opcode));
  return 2;
}

uint8_t srl_longmem(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_LONG_MEM(opcode) );
  return 4;
}

uint8_t srl_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT(X);
  return 1;
}

uint8_t srl_shortoff_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_OFF_X(opcode) );
  return 2;
}

uint8_t srl_longoff_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_LONG_OFF_X(opcode) );
  return 4;
}


uint8_t srl_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT(Y);
  return 2;
}

uint8_t srl_shortoff_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_OFF_Y(opcode) );
  return 3;
}

uint8_t srl_longoff_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_LONG_OFF_Y(opcode) );
  return 4;
}

uint8_t srl_shortoff_sp(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_OFF_SP(opcode) );
  return 2;
}

uint8_t srl_shortptr_w(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_PTR_W(opcode) );
  return 3;
}

uint8_t srl_longptr_w(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_LONG_PTR_W(opcode) );
  return 4;
}

uint8_t srl_shortptr_w_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_PTR_W_X(opcode) );
  return 3;
}

uint8_t srl_longptr_w_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_LONG_PTR_W_X(opcode) );
  return 4;
}

uint8_t srl_shortptr_w_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT( GET_SHORT_PTR_W_Y(opcode) ); 
  return 3;
}
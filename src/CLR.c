#include "CLR.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


//-----------------------Load mem to A----------------------------------------

uint8_t clr_a(uint8_t *opcode){
  A = 0;
  N = 0;
  Z = 1;
  return 1;
}

uint8_t clr_shortmem(uint8_t *opcode){
  CLEAR(GET_SHORT_MEM(opcode));
  return 2;
}

uint8_t clr_longmem(uint8_t *opcode){
  CLEAR(GET_LONG_MEM(opcode));
  return 4;
}

uint8_t clr_x(uint8_t *opcode){
  CLEAR(X);
  return 1;
}

uint8_t clr_shortoff_x(uint8_t *opcode){
  CLEAR(GET_SHORT_OFF_X(opcode));
  return 2;
}

uint8_t clr_longoff_x(uint8_t *opcode){
  CLEAR(GET_LONG_OFF_X(opcode));
  return 4;
}
  
uint8_t clr_y(uint8_t *opcode){
  CLEAR(Y);
  return 2;
}

uint8_t clr_shortoff_y(uint8_t *opcode){
  CLEAR(GET_SHORT_OFF_Y(opcode));
  return 3;
}

uint8_t clr_longoff_y(uint8_t *opcode){
  CLEAR(GET_LONG_OFF_Y(opcode));
  return 4;
}

uint8_t clr_shortoff_sp(uint8_t *opcode){
  CLEAR(GET_SHORT_OFF_SP(opcode));
  return 2;
}
  
uint8_t clr_shortptr_w(uint8_t *opcode){
  CLEAR(GET_SHORT_PTR_W(opcode));
  return 3;
}

uint8_t clr_longptr_w(uint8_t *opcode){
  CLEAR(GET_LONG_PTR_W(opcode));
  return 4;
}
uint8_t clr_shortptr_w_x(uint8_t *opcode){
  CLEAR(GET_SHORT_PTR_W_X(opcode));
  return 3;
}

uint8_t clr_longptr_w_x (uint8_t *opcode){
  CLEAR(GET_LONG_PTR_W_X(opcode));
  return 4;
}

uint8_t clr_shortptr_w_y(uint8_t *opcode){
  CLEAR(GET_SHORT_PTR_W_Y(opcode));
  return 3;
}
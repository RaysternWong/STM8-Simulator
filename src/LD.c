#include "LD.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


//-----------------------Load mem to A----------------------------------------

uint8_t ld_a_byte(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_NEXT_BYTE_OF(opcode));
  return 2;
}

uint8_t ld_a_shortmem(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_MEM_SRC(opcode));
  return 2;
}

uint8_t ld_a_longmem(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_MEM_SRC(opcode));
  return 3;
}

uint8_t ld_a_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, X_SRC);
  return 1;
}

uint8_t ld_a_shortoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_OFF_X_SRC(opcode));
  return 2;
}

uint8_t ld_a_longoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_OFF_X_SRC(opcode));
  return 3;
}
  
uint8_t ld_a_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, Y_SRC);
  return 2;
}

uint8_t ld_a_shortoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_OFF_Y_SRC(opcode));
  return 3;
}

uint8_t ld_a_longoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_OFF_Y_SRC(opcode));
  return 4;
}

uint8_t ld_a_shortoff_sp(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_OFF_SP_SRC(opcode));
  return 2;
}
  
uint8_t ld_a_shortptr_w(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_PTR_W_SRC(opcode));
  return 3;
}

uint8_t ld_a_longptr_w(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_PTR_W_SRC(opcode));
  return 4;
}
uint8_t ld_a_shortptr_w_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_PTR_W_X_SRC(opcode));
  return 3;
}

uint8_t ld_a_longptr_w_x (uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_PTR_W_X_SRC(opcode));
  return 4;
}

uint8_t ld_a_shortptr_w_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_SHORT_PTR_W_Y_SRC(opcode));
  return 3;
}

//-----------------------Load A to mem----------------------------------------

uint8_t ld_a_to_shortmem(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_NEXT_BYTE_OF(opcode), A);
  return 2;
}

uint8_t ld_a_to_longmem(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_LONG_MEM(opcode), A);
  return 3;
}

uint8_t ld_a_to_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(X, A);
  return 1;
}

uint8_t ld_a_to_shortoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_OFF_X(opcode), A);
  return 2;
}

uint8_t ld_a_to_longoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_LONG_OFF_X(opcode), A);
  return 3;
}
  
uint8_t ld_a_to_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(Y, A);
  return 2;
}

uint8_t ld_a_to_shortoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_OFF_Y(opcode), A);
  return 3;
}

uint8_t ld_a_to_longoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_LONG_OFF_Y(opcode), A);
  return 4;
}

uint8_t ld_a_to_shortoff_sp(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_OFF_SP(opcode), A);
  return 2;
}
  
uint8_t ld_a_to_shortptr_w(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_PTR_W(opcode), A);
  return 3;
}

uint8_t ld_a_to_longptr_w(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_LONG_PTR_W(opcode), A);
  return 4;
}
uint8_t ld_a_to_shortptr_w_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_PTR_W_X(opcode), A);
  return 3;
}

uint8_t ld_a_to_longptr_w_x (uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_LONG_PTR_W_X(opcode), A);
  return 4;
}

uint8_t ld_a_to_shortptr_w_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM(GET_SHORT_PTR_W_Y(opcode), A);
  return 3;
}

//-----------------load reg to reg-------

uint8_t ld_xl_a(uint8_t *opcode){
  XL = A;
  return 1;
}

uint8_t ld_a_xl(uint8_t *opcode){
  A = XL;
  return 1;
}

uint8_t ld_yl_a(uint8_t *opcode){
  YL = A;
  return 2;
}

uint8_t ld_a_yl(uint8_t *opcode){
  A = YL;
  return 2;
}

uint8_t ld_xh_a(uint8_t *opcode){
  XH = A;
  return 1;
}

uint8_t ld_a_xh(uint8_t *opcode){
  A = XH;
  return 1;
}

uint8_t ld_yh_a(uint8_t *opcode){
  YH = A;
  return 2;
}

uint8_t ld_a_yh(uint8_t *opcode){
  A = YH;
  return 2;
}
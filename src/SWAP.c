#include "SWAP.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define SWAP_REG(reg)  reg = SWAP_BYTE(reg); UPDATE_Z_N_FLAG(reg);
#define SWAP_MEM(mem)  uint8_t byte = SWAP_BYTE(MEM_READ_BYTE(mem)); MEM_WRITE_BYTE(mem, byte) ; UPDATE_Z_N_FLAG(byte);

uint8_t swap_a(uint8_t *opcode){
  SWAP_REG(A);
  return 1;
}

uint8_t swap_shortmem(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_MEM(opcode));
  return 2;
}

uint8_t swap_longmem(uint8_t *opcode){
  SWAP_MEM( GET_LONG_MEM(opcode) );
  return 4;
}

uint8_t swap_x(uint8_t *opcode){
  SWAP_MEM(X);
  return 1;
}

uint8_t swap_shortoff_x(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_OFF_X(opcode) );
  return 2;
}

uint8_t swap_longoff_x(uint8_t *opcode){
  SWAP_MEM( GET_LONG_OFF_X(opcode) );
  return 4;
}


uint8_t swap_y(uint8_t *opcode){
  SWAP_MEM( Y );
  return 2;
}

uint8_t swap_shortoff_y(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_OFF_Y(opcode) );
  return 3;
}

uint8_t swap_longoff_y(uint8_t *opcode){
  SWAP_MEM( GET_LONG_OFF_Y(opcode) );
  return 4;
}

uint8_t swap_shortoff_sp(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_OFF_SP(opcode) );
  return 2;
}

uint8_t swap_shortptr_w(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_PTR_W(opcode) );
  return 3;
}

uint8_t swap_longptr_w(uint8_t *opcode){
  SWAP_MEM( GET_LONG_PTR_W(opcode) );
  return 4;
}

uint8_t swap_shortptr_w_x(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_PTR_W_X(opcode) );
  return 3;
}

uint8_t swap_longptr_w_x(uint8_t *opcode){
  SWAP_MEM( GET_LONG_PTR_W_X(opcode) );
  return 4;
}

uint8_t swap_shortptr_w_y(uint8_t *opcode){
  SWAP_MEM( GET_SHORT_PTR_W_Y(opcode) ); 
  return 3;
}
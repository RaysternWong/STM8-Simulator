#include "SRA.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sra_a(uint8_t *opcode){
  REG_SHIFT_RIGHT_ARITHMETIC(A);
  return 1;
}

uint8_t sra_shortmem(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_MEM(opcode));
  return 2;
}

uint8_t sra_longmem(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_LONG_MEM(opcode) );
  return 4;
}

uint8_t sra_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC(X);
  return 1;
}

uint8_t sra_shortoff_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_OFF_X(opcode) );
  return 2;
}

uint8_t sra_longoff_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_LONG_OFF_X(opcode) );
  return 4;
}


uint8_t sra_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC(Y);
  return 2;
}

uint8_t sra_shortoff_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_OFF_Y(opcode) );
  return 3;
}

uint8_t sra_longoff_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_LONG_OFF_Y(opcode) );
  return 4;
}

uint8_t sra_shortoff_sp(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_OFF_SP(opcode) );
  return 2;
}

uint8_t sra_shortptr_w(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_PTR_W(opcode) );
  return 3;
}

uint8_t sra_longptr_w(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_LONG_PTR_W(opcode) );
  return 4;
}

uint8_t sra_shortptr_w_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_PTR_W_X(opcode) );
  return 3;
}

uint8_t sra_longptr_w_x(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_LONG_PTR_W_X(opcode) );
  return 4;
}

uint8_t sra_shortptr_w_y(uint8_t *opcode){
  MEM_SHIFT_RIGHT_ARITHMETIC( GET_SHORT_PTR_W_Y(opcode) ); 
  return 3;
}
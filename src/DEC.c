#include "DEC.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t dec_a(uint8_t *opcode){
  mcu_dec(A);
  return 1;
}

uint8_t dec_shortmem(uint8_t *opcode){
  mcu_dec(GET_SHORT_MEM(opcode)); 
  return 2;
}

uint8_t dec_longmem(uint8_t *opcode){
  mcu_dec(GET_LONG_MEM(opcode));
  return 4;
}

uint8_t dec_x(uint8_t *opcode){
  mcu_dec(X); 
  return 1;
}

uint8_t dec_shortoff_x(uint8_t *opcode){
  mcu_dec(GET_SHORT_OFF_X(opcode)); 
  return 2;
}

uint8_t dec_longoff_x(uint8_t *opcode){
  mcu_dec(GET_LONG_OFF_X(opcode)); 
  return 4;
}

uint8_t dec_y(uint8_t *opcode){
  mcu_dec(Y);
  return 2;
}

uint8_t dec_shortoff_y(uint8_t *opcode){
  mcu_dec(GET_SHORT_OFF_Y(opcode)); 
  return 3;
}

uint8_t dec_longoff_y(uint8_t *opcode){
  mcu_dec(GET_LONG_OFF_Y(opcode));  
  return 4;
}

uint8_t dec_shortoff_sp(uint8_t *opcode){
  mcu_dec(GET_SHORT_OFF_SP(opcode));
  return 2;
}

uint8_t dec_shortptr_w(uint8_t *opcode){
  mcu_dec(GET_SHORT_PTR_W(opcode));
  return 3;
}

uint8_t dec_longptr_w(uint8_t *opcode){
  mcu_dec(GET_LONG_PTR_W(opcode));
  return 4;
}

uint8_t dec_shortptr_w_x(uint8_t *opcode){
  mcu_dec(GET_SHORT_PTR_W_X(opcode));
  return 3;
}

uint8_t dec_longptr_w_x(uint8_t *opcode){
  mcu_dec(GET_LONG_PTR_W_X(opcode));
  return 4;
}

uint8_t dec_shortptr_w_y(uint8_t *opcode){
  mcu_dec(GET_SHORT_PTR_W_Y(opcode)); 
  return 3;
}
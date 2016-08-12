#include "LDW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

//-----------------------Load mem word to X----------------------------------------
uint8_t ldw_x_word(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_LONG_MEM(opcode));
  return 3;
}

uint8_t ldw_x_shortmem(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_SHORT_MEM_WORD(opcode));
  return 2;
}

uint8_t ldw_x_longmem(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_LONG_MEM_WORD(opcode));
  return 3;
}

uint8_t ldw_x_x(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, WORD_HOLD_BY_X);
  return 1;
}

uint8_t ldw_x_shortoff_x(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_SHORT_OFF_X_WORD(opcode));
  return 2;
}

uint8_t ldw_x_longoff_x(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_LONG_OFF_X_WORD(opcode));
  return 3;
}
  
uint8_t ldw_x_shortoff_sp(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_SHORT_OFF_SP_WORD(opcode));
  return 2;
}

uint8_t ldw_x_shortptr_w(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_SHORT_PTR_W_WORD(opcode));
  return 3;
}

uint8_t ldw_x_longptr_w(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_LONG_PTR_W_WORD(opcode));
  return 4;
}

uint8_t ldw_x_shortptr_w_x(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_SHORT_PTR_W_X_WORD(opcode));
  return 3;
}

uint8_t ldw_x_longptr_w_x(uint8_t *opcode){
  LOAD_WORD_TO_REG( XH, GET_LONG_PTR_W_X_WORD(opcode));
  return 4;
}

//-----------------------Load mem word to Y----------------------------------------
uint8_t ldw_y_word(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_LONG_MEM(opcode));
  return 4;
}

uint8_t ldw_y_shortmem(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_SHORT_MEM_WORD(opcode));
  return 3;
}

uint8_t ldw_y_longmem(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_LONG_MEM_WORD(opcode));
  return 4;
}

uint8_t ldw_y_y(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, WORD_HOLD_BY_Y);
  return 2;
}

uint8_t ldw_y_shortoff_y(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_SHORT_OFF_Y_WORD(opcode));
  return 3;
}

uint8_t ldw_y_longoff_y(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_LONG_OFF_Y_WORD(opcode));
  return 4;
}
  
uint8_t ldw_y_shortoff_sp(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_SHORT_OFF_SP_WORD(opcode));
  return 2;
}

uint8_t ldw_y_shortptr_w(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_SHORT_PTR_W_WORD(opcode));
  return 3;
}

uint8_t ldw_y_shortptr_w_y(uint8_t *opcode){
  LOAD_WORD_TO_REG( YH, GET_SHORT_PTR_W_Y_WORD(opcode));
  return 3;
}

//-----------------------Load reg to mem----------------------------------------
// For X
uint8_t ldw_x_to_shortmem(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_MEM(opcode), X);
  return 2;
}

uint8_t ldw_x_to_longmem(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_MEM(opcode), X);
  return 3;
}

uint8_t ldw_y_to_x(uint8_t *opcode){
  LOAD_WORD_TO_MEM(WORD_HOLD_BY_X, Y);
  return 1;
}

uint8_t ldw_y_to_shortoff_x(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_OFF_X(opcode), Y);
  return 2;
}

uint8_t ldw_y_to_longoff_x(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_OFF_X(opcode), Y);
  return 3;
}

uint8_t ldw_x_to_shortoff_sp(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_OFF_SP(opcode), X);
  return 2;
}

uint8_t ldw_x_to_shortptr_w(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_PTR_W(opcode), X);
  return 3;
}

uint8_t ldw_x_to_longptr_w(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_PTR_W(opcode), X);
  return 4;
}

uint8_t ldw_y_to_shortptr_w_x(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_PTR_W_X(opcode), Y);
  return 3;
}

uint8_t ldw_y_to_longptr_w_x(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_PTR_W_X(opcode), Y);
  return 4;
}

//For Y
uint8_t ldw_y_to_shortmem(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_NEXT_BYTE_OF(opcode), Y);
  return 3;  
}

uint8_t ldw_y_to_longmem(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_MEM(opcode), Y);
  return 4;  
}

uint8_t ldw_x_to_y(uint8_t *opcode){
  LOAD_WORD_TO_MEM(WORD_HOLD_BY_Y, X);
  return 2;  
}

uint8_t ldw_x_to_shortoff_y(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_OFF_Y(opcode), X);
  return 3;  
}

uint8_t ldw_x_to_longoff_y(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_LONG_OFF_Y(opcode), X);
  return 4;  
}

uint8_t ldw_y_to_shortoff_sp(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_OFF_SP(opcode), Y);
  return 2;  
}

uint8_t ldw_y_to_shortptr_w(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_PTR_W(opcode), Y);
  return 3;  
}

uint8_t ldw_x_to_shortptr_w_y(uint8_t *opcode){
  LOAD_WORD_TO_MEM(GET_SHORT_PTR_W_Y(opcode), X);
  return 3;  
}

// load reg to reg

uint8_t ldw_y_x  (uint8_t *opcode){
  SET_Y(X);
  return 2;
}
uint8_t ldw_x_y  (uint8_t *opcode){
  SET_X(Y);
  return 1;  
}

uint8_t ldw_x_sp  (uint8_t *opcode){
  SET_X(SP);
  return 1;  
}

uint8_t ldw_sp_x  (uint8_t *opcode){
  SET_SP(X);
  return 1;  
}

uint8_t ldw_y_sp  (uint8_t *opcode){
  SET_Y(SP);
  return 2;  
}

uint8_t ldw_sp_y  (uint8_t *opcode){
  SET_SP(Y);
  return 2;  
}


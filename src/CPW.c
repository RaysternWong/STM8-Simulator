#include "CPW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t cpw_x_word(uint8_t *opcode){
  mcu_cpw(X, GET_LONG_MEM(opcode) );
  return 3;
}

uint8_t cpw_x_shortmem(uint8_t *opcode){
  mcu_cpw(X, GET_SHORT_MEM_SRC(opcode));
  return 2;
}

uint8_t cpw_x_longmem(uint8_t *opcode){
  mcu_cpw(X, GET_LONG_MEM_SRC(opcode) );
  return 3;
}

uint8_t cpw_x_y(uint8_t *opcode){
  mcu_cpw(X, Y_SRC );
  return 2;
}

uint8_t cpw_x_shortoff_y(uint8_t *opcode){
  mcu_cpw(X, GET_SHORT_OFF_Y_SRC(opcode) );
  return 3;
}

uint8_t cpw_x_longoff_y(uint8_t *opcode){
  mcu_cpw(X, GET_LONG_OFF_Y_SRC(opcode) );
  return 4;
}

uint8_t cpw_x_shortoff_sp(uint8_t *opcode){
  mcu_cpw(X, GET_SHORT_OFF_SP_SRC(opcode) );
  return 2;
}

uint8_t cpw_x_shortptr_w(uint8_t *opcode){
  mcu_cpw(X, GET_SHORT_PTR_W_SRC(opcode) );
  return 3;
}

uint8_t cpw_x_longptr_w(uint8_t *opcode){
  mcu_cpw(X, GET_LONG_PTR_W_SRC(opcode) );
  return 4;
}

uint8_t cpw_x_shortptr_w_y(uint8_t *opcode){
  mcu_cpw(X, GET_SHORT_PTR_W_Y_SRC(opcode) ); 
  return 3;
}


// For Y


uint8_t cpw_y_word(uint8_t *opcode){
  mcu_cpw(Y, GET_LONG_MEM(opcode) );
  return 4;
}

uint8_t cpw_y_shortmem(uint8_t *opcode){
  mcu_cpw(Y, GET_SHORT_MEM_SRC(opcode));
  return 3;
}

uint8_t cpw_y_longmem(uint8_t *opcode){
  mcu_cpw(Y, GET_LONG_MEM_SRC(opcode) );
  return 4;
}

uint8_t cpw_y_x(uint8_t *opcode){
  mcu_cpw(Y, X_SRC );
  return 1;
}

uint8_t cpw_y_shortoff_x(uint8_t *opcode){
  mcu_cpw(Y, GET_SHORT_OFF_X_SRC(opcode) );
  return 2;
}

uint8_t cpw_y_longoff_x(uint8_t *opcode){
  mcu_cpw(Y, GET_LONG_OFF_X_SRC(opcode) );
  return 3;
}

uint8_t cpw_y_shortptr_w(uint8_t *opcode){
  mcu_cpw(Y, GET_SHORT_PTR_W_SRC(opcode) );
  return 3;
}

uint8_t cpw_y_shortptr_w_x(uint8_t *opcode){
  mcu_cpw(Y, GET_SHORT_PTR_W_X_SRC(opcode) ); 
  return 3;
}

uint8_t cpw_y_longptr_w_x(uint8_t *opcode){
  mcu_cpw(Y, GET_LONG_PTR_W_X_SRC(opcode) );
  return 4;
}
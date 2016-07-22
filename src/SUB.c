#include "SUB.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sub_a_byte(uint8_t *opcode){
  mcu_sub( GET_NEXT_BYTE_OF(opcode) );
  return 2;
}

uint8_t sub_a_shortmem(uint8_t *opcode){
  mcu_sub(GET_SHORT_MEM_SRC(opcode));
  return 2;
}

uint8_t sub_a_longmem(uint8_t *opcode){
  mcu_sub( GET_LONG_MEM_SRC(opcode) );
  return 3;
}


uint8_t sub_a_x(uint8_t *opcode){
  mcu_sub( X_SRC);
  return 1;
}

uint8_t sub_a_shortoff_x(uint8_t *opcode){
  mcu_sub( GET_SHORT_OFF_X_SRC(opcode) );
  return 2;
}

uint8_t sub_a_longoff_x(uint8_t *opcode){
  mcu_sub( GET_LONG_OFF_X_SRC(opcode) );
  return 3;
}


uint8_t sub_a_y(uint8_t *opcode){
  mcu_sub(  Y_SRC );
  return 2;
}

uint8_t sub_a_shortoff_y(uint8_t *opcode){
  mcu_sub( GET_SHORT_OFF_Y_SRC(opcode) );
  return 3;
}

uint8_t sub_a_longoff_y(uint8_t *opcode){
  mcu_sub( GET_LONG_OFF_Y_SRC(opcode) );
  return 4;
}

uint8_t sub_a_shortoff_sp(uint8_t *opcode){
  mcu_sub( GET_SHORT_OFF_SP_SRC(opcode) );
  return 2;
}

uint8_t sub_a_shortptr_w(uint8_t *opcode){
  mcu_sub( GET_SHORT_PTR_W_SRC(opcode) );
  return 3;
}

uint8_t sub_a_longptr_w(uint8_t *opcode){
  mcu_sub( GET_LONG_PTR_W_SRC(opcode) );
  return 4;
}

uint8_t sub_a_shortptr_w_x(uint8_t *opcode){
  mcu_sub( GET_SHORT_PTR_W_X_SRC(opcode) );
  return 3;
}

uint8_t sub_a_longptr_w_x(uint8_t *opcode){
  mcu_sub( GET_LONG_PTR_W_X_SRC(opcode) );
  return 4;
}

uint8_t sub_a_shortptr_w_y(uint8_t *opcode){
  mcu_sub( GET_SHORT_PTR_W_Y_SRC(opcode) ); 
  return 3;
}

uint8_t sub_sp_byte(uint8_t *opcode){
  
  uint16_t a      = SP;
  uint8_t  value  = GET_NEXT_BYTE_OF(opcode) ;
  uint16_t result = a - value;

  SET_SP(result);

  N = R7;
  Z = (result == 0 ? 1 : 0);
  C = _A7 & M7 | _A7 & R7 | A7 & M7 & A7;
  V = (A7 & M7 | A7 & R7 | A7 & M7 & R7) ^ (A6 & M6 | A6 & R6 | A6 & M6 & R6) ;
  return 2;
}
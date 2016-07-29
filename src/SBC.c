#include "SBC.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sbc_a_byte(uint8_t *opcode){
  mcu_sbc( GET_NEXT_BYTE_OF(opcode) );
  return 2;
}

uint8_t sbc_a_shortmem(uint8_t *opcode){
  mcu_sbc(GET_SHORT_MEM_SRC(opcode));
  return 2;
}

uint8_t sbc_a_longmem(uint8_t *opcode){
  mcu_sbc( GET_LONG_MEM_SRC(opcode) );
  return 3;
}

uint8_t sbc_a_x(uint8_t *opcode){
  mcu_sbc( X_SRC);
  return 1;
}

uint8_t sbc_a_shortoff_x(uint8_t *opcode){
  mcu_sbc( GET_SHORT_OFF_X_SRC(opcode) );
  return 2;
}

uint8_t sbc_a_longoff_x(uint8_t *opcode){
  mcu_sbc( GET_LONG_OFF_X_SRC(opcode) );
  return 3;
}


uint8_t sbc_a_y(uint8_t *opcode){
  mcu_sbc(  Y_SRC );
  return 2;
}

uint8_t sbc_a_shortoff_y(uint8_t *opcode){
  mcu_sbc( GET_SHORT_OFF_Y_SRC(opcode) );
  return 3;
}

uint8_t sbc_a_longoff_y(uint8_t *opcode){
  mcu_sbc( GET_LONG_OFF_Y_SRC(opcode) );
  return 4;
}

uint8_t sbc_a_shortoff_sp(uint8_t *opcode){
  mcu_sbc( GET_SHORT_OFF_SP_SRC(opcode) );
  return 2;
}

uint8_t sbc_a_shortptr_w(uint8_t *opcode){
  mcu_sbc( GET_SHORT_PTR_W_SRC(opcode) );
  return 3;
}

uint8_t sbc_a_longptr_w(uint8_t *opcode){
  mcu_sbc( GET_LONG_PTR_W_SRC(opcode) );
  return 4;
}

uint8_t sbc_a_shortptr_w_x(uint8_t *opcode){
  mcu_sbc( GET_SHORT_PTR_W_X_SRC(opcode) );
  return 3;
}

uint8_t sbc_a_longptr_w_x(uint8_t *opcode){
  mcu_sbc( GET_LONG_PTR_W_X_SRC(opcode) );
  return 4;
}

uint8_t sbc_a_shortptr_w_y(uint8_t *opcode){
  mcu_sbc( GET_SHORT_PTR_W_Y_SRC(opcode) ); 
  return 3;
}
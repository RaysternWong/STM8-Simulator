#include "TNZ.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t tnz_a(uint8_t *opcode){
  UPDATE_Z_N_FLAG( A );
  return 1;
}

uint8_t tnz_shortmem(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_MEM_SRC(opcode));
  return 2;
}

uint8_t tnz_longmem(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_LONG_MEM_SRC(opcode) );
  return 4;
}

uint8_t tnz_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG(X_SRC);
  return 1;
}

uint8_t tnz_shortoff_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_OFF_X_SRC(opcode) );
  return 2;
}

uint8_t tnz_longoff_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_LONG_OFF_X_SRC(opcode) );
  return 4;
}


uint8_t tnz_y(uint8_t *opcode){
  UPDATE_Z_N_FLAG( Y_SRC );
  return 2;
}

uint8_t tnz_shortoff_y(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_OFF_Y_SRC(opcode) );
  return 3;
}

uint8_t tnz_longoff_y(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_LONG_OFF_Y_SRC(opcode) );
  return 4;
}

uint8_t tnz_shortoff_sp(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_OFF_SP_SRC(opcode) );
  return 2;
}

uint8_t tnz_shortptr_w(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_PTR_W_SRC(opcode) );
  return 3;
}

uint8_t tnz_longptr_w(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_LONG_PTR_W_SRC(opcode) );
  return 4;
}

uint8_t tnz_shortptr_w_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_PTR_W_X_SRC(opcode) );
  return 3;
}

uint8_t tnz_longptr_w_x(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_LONG_PTR_W_X_SRC(opcode) );
  return 4;
}

uint8_t tnz_shortptr_w_y(uint8_t *opcode){
  UPDATE_Z_N_FLAG( GET_SHORT_PTR_W_Y_SRC(opcode) ); 
  return 3;
}
#include "JP.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t jp_longmem(uint8_t *opcode){ 
  *pcToLoad = GET_LONG_MEM(opcode);
  return 3;
}

uint8_t jp_x(uint8_t *opcode){
  *pcToLoad = X;
  return 1;
}

uint8_t jp_shortoff_x(uint8_t *opcode){
  *pcToLoad = GET_SHORT_OFF_X(opcode);
  return 2;
}

uint8_t jp_longoff_x(uint8_t *opcode){ 
  *pcToLoad = GET_LONG_OFF_X(opcode);
  return 3;
}

uint8_t jp_y(uint8_t *opcode){
  *pcToLoad = Y;
  return 2;
}
  
uint8_t jp_shortoff_y(uint8_t *opcode){
  *pcToLoad = GET_SHORT_OFF_Y(opcode);
  return 3;
}

uint8_t jp_longoff_y(uint8_t *opcode){ 
  *pcToLoad = GET_LONG_OFF_Y(opcode);
  return 4;
}

uint8_t jp_shortptr_w(uint8_t *opcode){
  *pcToLoad = GET_SHORT_PTR_W(opcode);
  return 3;
}
  
uint8_t jp_longptr_w(uint8_t *opcode){
  *pcToLoad = GET_LONG_PTR_W(opcode);
  return 4;
}

uint8_t jp_shortptr_w_x(uint8_t *opcode){ 
  *pcToLoad = GET_SHORT_PTR_W_X(opcode);
  return 3;
}

uint8_t jp_longptr_w_x(uint8_t *opcode){ 
  *pcToLoad = GET_LONG_PTR_W_X(opcode);
  return 4;
}

uint8_t jp_shortptr_w_y(uint8_t *opcode){ 
  *pcToLoad = GET_SHORT_PTR_W_Y(opcode);
  return 3;
}
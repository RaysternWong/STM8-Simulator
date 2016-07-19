#include "AND.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t and_a_byte(uint8_t *opcode){
  A &= GET_BYTE(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t and_a_shortmem(uint8_t *opcode){
  A &=getShortMemSrc(opcode);
  return 2;
}

uint8_t and_a_longmem(uint8_t *opcode){
  A &= getLongMemSrc(opcode);
  return 3;
}


uint8_t and_a_x(uint8_t *opcode){
  A &= X_SRC;
  return 1;
}

uint8_t and_a_shortoff_x(uint8_t *opcode){
  A &= getShortOffXSrc(opcode);
  return 2;
}

uint8_t and_a_longoff_x(uint8_t *opcode){
  A &= getLongOffXSrc(opcode);
  return 3;
}


uint8_t and_a_y(uint8_t *opcode){
  A &= Y_SRC;
  return 2;
}

uint8_t and_a_shortoff_y(uint8_t *opcode){
  A &= getShortOffYSrc(opcode);
  return 3;
}

uint8_t and_a_longoff_y(uint8_t *opcode){
  A &= getLongOffYSrc(opcode);
  return 4;
}

uint8_t and_a_shortoff_sp(uint8_t *opcode){
  A &= getShortOffSPSrc(opcode);
  return 2;
}

uint8_t and_a_shortptr_w(uint8_t *opcode){
  A &= getShortPtrWSrc(opcode);
  return 3;
}

uint8_t and_a_longptr_w(uint8_t *opcode){
  A &= getLongPtrWSrc(opcode);
  return 4;
}

uint8_t and_a_shortptr_w_x(uint8_t *opcode){
  A &= getShortPtrWXSrc(opcode) ;
  return 3;
}

uint8_t and_a_longptr_w_x(uint8_t *opcode){
  A &= getLongPtrWXSrc(opcode) ;
  return 4;
}

uint8_t and_a_shortptr_w_y(uint8_t *opcode){
  A &= getShortPtrWYSrc(opcode) ; 
  return 3;
}


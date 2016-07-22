#include "XOR.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t xor_a_byte(uint8_t *opcode){
  A ^= GET_NEXT_BYTE_OF(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t xor_a_shortmem(uint8_t *opcode){
  A ^= getShortMemSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t xor_a_longmem(uint8_t *opcode){
  A ^= getLongMemSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 3;
}


uint8_t xor_a_x(uint8_t *opcode){
  A ^= X_SRC;
  SET_ARITHMETIC_FLAG(A);
  return 1;
}

uint8_t xor_a_shortoff_x(uint8_t *opcode){
  A ^= getShortOffXSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t xor_a_longoff_x(uint8_t *opcode){
  A ^= getLongOffXSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 3;
}


uint8_t xor_a_y(uint8_t *opcode){
  A ^= Y_SRC;
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t xor_a_shortoff_y(uint8_t *opcode){
  A ^= getShortOffYSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 3;
}

uint8_t xor_a_longoff_y(uint8_t *opcode){
  A ^= getLongOffYSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 4;
}

uint8_t xor_a_shortoff_sp(uint8_t *opcode){
  A ^= getShortOffSPSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 2;
}

uint8_t xor_a_shortptr_w(uint8_t *opcode){
  A ^= getShortPtrWSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 3;
}

uint8_t xor_a_longptr_w(uint8_t *opcode){
  A ^= getLongPtrWSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 4;
}

uint8_t xor_a_shortptr_w_x(uint8_t *opcode){
  A ^= getShortPtrWXSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 3;
}

uint8_t xor_a_longptr_w_x(uint8_t *opcode){
  A ^= getLongPtrWXSrc(opcode);
  SET_ARITHMETIC_FLAG(A);
  return 4;
}

uint8_t xor_a_shortptr_w_y(uint8_t *opcode){
  A ^= getShortPtrWYSrc(opcode); 
  SET_ARITHMETIC_FLAG(A);
  return 3;
}


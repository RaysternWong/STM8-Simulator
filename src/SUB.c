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
  mcu_sub(getShortMemSrc(opcode));
  return 2;
}

uint8_t sub_a_longmem(uint8_t *opcode){
  mcu_sub( getLongMemSrc(opcode) );
  return 3;
}

uint8_t sub_a_x(uint8_t *opcode){
  mcu_sub( X_SRC);
  return 1;
}

uint8_t sub_a_shortoff_x(uint8_t *opcode){
  mcu_sub( getShortOffXSrc(opcode) );
  return 2;
}

uint8_t sub_a_longoff_x(uint8_t *opcode){
  mcu_sub( getLongOffXSrc(opcode) );
  return 3;
}

uint8_t sub_a_y(uint8_t *opcode){
  mcu_sub(  Y_SRC );
  return 2;
}

uint8_t sub_a_shortoff_y(uint8_t *opcode){
  mcu_sub( getShortOffYSrc(opcode) );
  return 3;
}

uint8_t sub_a_longoff_y(uint8_t *opcode){
  mcu_sub( getLongOffYSrc(opcode) );
  return 4;
}

uint8_t sub_a_shortoff_sp(uint8_t *opcode){
  mcu_sub( getShortOffSPSrc(opcode) );
  return 2;
}

uint8_t sub_a_shortptr_w(uint8_t *opcode){
  mcu_sub( getShortPtrWSrc(opcode) );
  return 3;
}

uint8_t sub_a_longptr_w(uint8_t *opcode){
  mcu_sub( getLongPtrWSrc(opcode) );
  return 4;
}

uint8_t sub_a_shortptr_w_x(uint8_t *opcode){
  mcu_sub( getShortPtrWXSrc(opcode) );
  return 3;
}

uint8_t sub_a_longptr_w_x(uint8_t *opcode){
  mcu_sub( getLongPtrWXSrc(opcode) );
  return 4;
}

uint8_t sub_a_shortptr_w_y(uint8_t *opcode){
  mcu_sub( getShortPtrWYSrc(opcode) ); 
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
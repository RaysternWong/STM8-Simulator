#include "ADD.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t add_a_byte(uint8_t *opcode){
  mcu_add( GET_BYTE(opcode) );
  return 2;
}

uint8_t add_a_shortmem(uint8_t *opcode){
  mcu_add(getShortMemSrc(opcode));
  return 2;
}

uint8_t add_a_longmem(uint8_t *opcode){
  mcu_add( getLongMemSrc(opcode) );
  return 3;
}


uint8_t add_a_x(uint8_t *opcode){

  mcu_add( X_SRC);
  return 1;
}

uint8_t add_a_shortoff_x(uint8_t *opcode){
  mcu_add( getShortOffXSrc(opcode) );
  return 2;
}

uint8_t add_a_longoff_x(uint8_t *opcode){
  mcu_add( getLongOffXSrc(opcode) );
  return 3;
}


uint8_t add_a_y(uint8_t *opcode){
  mcu_add(  Y_SRC );
  return 2;
}

uint8_t add_a_shortoff_y(uint8_t *opcode){
  mcu_add( getShortOffYSrc(opcode) );
  return 3;
}

uint8_t add_a_longoff_y(uint8_t *opcode){
  mcu_add( getLongOffYSrc(opcode) );
  return 4;
}

uint8_t add_a_shortoff_sp(uint8_t *opcode){
  mcu_add( getShortOffSPSrc(opcode) );
  return 2;
}

uint8_t add_a_shortptr_w(uint8_t *opcode){
  mcu_add( getShortPtrWSrc(opcode) );
  return 3;
}

uint8_t add_a_longptr_w(uint8_t *opcode){
  mcu_add( getLongPtrWSrc(opcode) );
  return 4;
}

uint8_t add_a_shortptr_w_x(uint8_t *opcode){
  mcu_add( getShortPtrWXSrc(opcode) );
  return 3;
}

uint8_t add_a_longptr_w_x(uint8_t *opcode){
  mcu_add( getLongPtrWXSrc(opcode) );
  return 4;
}

uint8_t add_a_shortptr_w_y(uint8_t *opcode){
  mcu_add( getShortPtrWYSrc(opcode) ); 
  return 3;
}




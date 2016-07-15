#include "CALL.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t call_longmem(uint8_t *opcode){ 
  mcu_call( GET_LONG_MEM(opcode), 3 );
  return 3;
}

uint8_t call_x(uint8_t *opcode){
  mcu_call( X, 1 );
  return 1;
}

uint8_t call_shortoff_x(uint8_t *opcode){
  mcu_call( GET_SHORT_OFF_X(opcode), 2 );
  return 2;
}

uint8_t call_longoff_x(uint8_t *opcode){ 
  mcu_call( GET_LONG_OFF_X(opcode), 3 );
  return 3;
}

uint8_t call_y(uint8_t *opcode){
  mcu_call( Y, 2 );
  return 2;
}
  
uint8_t call_shortoff_y(uint8_t *opcode){
  mcu_call( GET_SHORT_OFF_Y(opcode), 3 );
  return 3;
}

uint8_t call_longoff_y(uint8_t *opcode){ 
  mcu_call( GET_LONG_OFF_Y(opcode), 4);
  return 4;
}

uint8_t call_shortptr_w(uint8_t *opcode){
  mcu_call( GET_SHORT_PTR_W(opcode), 3 );
  return 3;
}
  
uint8_t call_longptr_w(uint8_t *opcode){
  mcu_call( GET_LONG_PTR_W(opcode), 4);
  return 4;
}

uint8_t call_shortptr_w_x(uint8_t *opcode){ 
  mcu_call( GET_SHORT_PTR_W_X(opcode), 3 );
  return 3;
}

uint8_t call_longptr_w_x(uint8_t *opcode){ 
  mcu_call( GET_LONG_PTR_W_X(opcode), 4 );
  return 4;
}

uint8_t call_shortptr_w_y(uint8_t *opcode){ 
  mcu_call( GET_SHORT_PTR_W_Y(opcode), 3 );
  return 3;
}



#include "CALL.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t call_longmem(uint8_t *opcode){
  uint8_t address = getlongmemSrc(opcode);
  mcu_call( address, 3);
  return 3;
}

uint8_t call_x(uint8_t *opcode){
  mcu_call( X, 1);
  return 1;  
}

uint8_t call_y(uint8_t *opcode){
  mcu_call( Y, 2);
  return 2;
}

uint8_t call_shortoff_x(uint8_t *opcode){
  uint8_t address =  getShortOffX(opcode);
  mcu_call( address, 2);
  return 2;
}

uint8_t call_shortoff_y(uint8_t *opcode){
  uint8_t address =  getShortOffY(opcode);
  mcu_call( address, 3);
  return 3;  
}

uint8_t call_longoff_x(uint8_t *opcode){
  uint8_t address =  getLongOffX(opcode);;
  mcu_call( address, 3);
  return 3;
}


uint8_t call_longoff_y(uint8_t *opcode){
  uint8_t address =  getLongOffY(opcode);;
  mcu_call( address, 4);
  return 4;  
}

uint8_t call_shortptr(uint8_t *opcode){
  uint8_t address =  getShortPtr(opcode);
  mcu_call( address, 3);
  return 3;  
}

uint8_t call_longptr(uint8_t *opcode){
  uint8_t address =  getLongPtr(opcode);
  mcu_call( address, 4);
  return 4;  
}

uint8_t call_shortptr_x(uint8_t *opcode){
  uint8_t address =  getShortPtrX(opcode);
  mcu_call( address, 3);
  return 3;  
}

uint8_t call_shortptr_y(uint8_t *opcode){
  uint8_t address =  getShortPtrY(opcode);
  mcu_call( address, 3);
  return 3;  
}

uint8_t call_longptr_x(uint8_t *opcode){
  uint8_t address =  getLongPtrX(opcode);
  mcu_call( address, 4);
  return 4;  
}


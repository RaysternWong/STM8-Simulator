#include "ADD.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

/**
*   ht means hast tag (#)
*
*   Please refer the following fuction in the page 77 of programming manual
*/ 

uint8_t add_a_ht_byte(uint8_t *opcode){
  opcode++;
  mcu_add(*opcode);
  return 2;
}

uint8_t add_a_shortmem(uint8_t *opcode){
  opcode++;
  int value = mcu_memory[*opcode];
  mcu_add(value);
  return 2;
}

uint8_t add_a_longmem(uint8_t *opcode){
  opcode++;
  int v1 = (*opcode) * 100;
  int v2 = *(++opcode);
  
  uint8_t value = mcu_memory[v1+v2];
  mcu_add(value);
  return 3;
}

uint8_t add_a_x(uint8_t *opcode){
  opcode++;
  uint8_t value = mcu_memory[cpu.index_X];
  mcu_add(value);
  return 1;
}

uint8_t add_a_shortoff_x(uint8_t *opcode){
  opcode++;
  
  uint8_t value = mcu_memory[cpu.index_X + *opcode];
  mcu_add(value);
  return 2;
}

uint8_t add_a_longoff_x(uint8_t *opcode){
  opcode++;
  int v1 = (*opcode) * 100;
  int v2 = *(++opcode);
  
  // printf("%d\n",v1);
  // printf("%d\n",v2);
  // printf("%d\n",cpu.index_X);
  
  uint8_t value = mcu_memory[ cpu.index_X + v1+v2];
  mcu_add(value);
  return 3;
}

uint8_t add_a_y(uint8_t *opcode){
  opcode++;
  uint8_t value = mcu_memory[cpu.index_Y];
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortoff_y(uint8_t *opcode){
  opcode++;
  
  uint8_t value = mcu_memory[cpu.index_Y + *opcode];
  mcu_add(value);
  return 3;
}

uint8_t add_a_longoff_y(uint8_t *opcode){
  opcode++;
  int v1 = (*opcode) * 100;
  int v2 = *(++opcode);
  
  uint8_t value = mcu_memory[ cpu.index_Y + v1+v2];
  mcu_add(value);
  return 4;
}

uint8_t add_a_shortoff_sp(uint8_t *opcode){
  opcode++;
  
  uint8_t value = mcu_memory[cpu.sp + *opcode];
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortptr_w(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t add_a_longptr_w(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t add_a_shortptr_w_x(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t add_a_longptr_w_x(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t add_a_shortptr_w_y(uint8_t *opcode){
  opcode++;
  return 3;
}





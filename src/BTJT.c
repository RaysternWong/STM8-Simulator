#include "BTJT.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define BTJT(GET_BIT_N) uint16_t longmem = GET_LONG_MEM(opcode); C = GET_BIT_N(MEM_READ_BYTE(longmem)); int8_t rel = *(3+opcode) ; *pcToLoad = (C == 1 ? PC+5+rel : PC+5 ) 

uint8_t btjt_longmem_pos_0(uint8_t *opcode){ 
  BTJT(GET_BIT_0);
  return 5;
}

uint8_t btjt_longmem_pos_1(uint8_t *opcode){
  BTJT(GET_BIT_1);
  return 5;
}

uint8_t btjt_longmem_pos_2(uint8_t *opcode){
  BTJT(GET_BIT_2);
  return 5;
}

uint8_t btjt_longmem_pos_3(uint8_t *opcode){
  BTJT(GET_BIT_3);
  return 5;
}

uint8_t btjt_longmem_pos_4(uint8_t *opcode){
  BTJT(GET_BIT_4);
  return 5;
}

uint8_t btjt_longmem_pos_5(uint8_t *opcode){
  BTJT(GET_BIT_5);
  return 5;
}
uint8_t btjt_longmem_pos_6(uint8_t *opcode){
  BTJT(GET_BIT_6);
  return 5;
}

uint8_t btjt_longmem_pos_7(uint8_t *opcode){
  BTJT(GET_BIT_7);
  return 5;
}
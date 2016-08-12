#include "BSET.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define BSET(num) uint16_t longmem = GET_LONG_MEM(opcode); MEM_WRITE_BYTE(longmem, MEM_READ_BYTE(longmem) | num );

uint8_t bset_longmem_pos_0(uint8_t *opcode){
  BSET(0x1);
  return 4;
}

uint8_t bset_longmem_pos_1(uint8_t *opcode){
  BSET(0x2);
  return 4;
}

uint8_t bset_longmem_pos_2(uint8_t *opcode){
  BSET(0x4);
  return 4;
}

uint8_t bset_longmem_pos_3(uint8_t *opcode){
  BSET(0x8);
  return 4;
}

uint8_t bset_longmem_pos_4(uint8_t *opcode){
  BSET(0x10);
  return 4;
}

uint8_t bset_longmem_pos_5(uint8_t *opcode){
  BSET(0x20);
  return 4;
}
uint8_t bset_longmem_pos_6(uint8_t *opcode){
  BSET(0x40);
  return 4;
}

uint8_t bset_longmem_pos_7(uint8_t *opcode){
  BSET(0x80);
  return 4;
}
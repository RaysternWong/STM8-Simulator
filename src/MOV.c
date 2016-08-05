#include "MOV.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t mov_longmem_byte(uint8_t *opcode){
  uint8_t byte = INC_THIS(opcode);
  uint16_t longmem = GET_LONG_MEM(opcode);
  MEM_WRITE_BYTE( longmem , byte );
  return 4;
}

uint8_t mov_shortmem_shortmem(uint8_t *opcode){
  uint8_t shortmen2 = INC_THIS(opcode);
  uint8_t shortmen1 = INC_THIS(opcode);
  MEM_WRITE_BYTE( shortmen1 , MEM_READ_BYTE(shortmen2) );
  return 3;
}

uint8_t mov_longmem_longmem(uint8_t *opcode){
  uint16_t longmem2 = GET_LONG_MEM(opcode++);
  uint16_t longmem1 = GET_LONG_MEM(++opcode);
  MEM_WRITE_BYTE( longmem1 , MEM_READ_BYTE(longmem2) );
  return 5;
}
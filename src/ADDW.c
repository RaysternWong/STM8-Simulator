#include "ADDW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t addw_x_word(uint8_t *opcode){
  mcu_addw(&XH, GET_WORD(opcode));
  return 3;
}


uint8_t addw_x_longmem(uint8_t *opcode){
  mcu_addw(&XH, GET_LONG_MEM_SRC(opcode));
  return 4;
}

uint8_t addw_x_shortoff_sp(uint8_t *opcode){
  mcu_addw(&XH, GET_SHORT_OFF_SP_SRC(opcode));
  return 3;
}

uint8_t addw_y_word(uint8_t *opcode){
  mcu_addw(&YH, GET_WORD(opcode));
  return 4;
}

uint8_t addw_y_longmem(uint8_t *opcode){
  mcu_addw(&YH, GET_LONG_MEM_SRC(opcode));
  return 4;
}

uint8_t addw_y_shortoff_sp(uint8_t *opcode){
  mcu_addw(&YH, GET_SHORT_OFF_SP_SRC(opcode));
  return 3;
}

uint8_t addw_sp_byte(uint8_t *opcode){
  mcu_addw(&SPH, GET_NEXT_BYTE_OF(opcode));
  return 2;
}
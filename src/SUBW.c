#include "SUBW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t subw_x_word(uint8_t *opcode){
  mcu_subw(&XH, GET_LONG_MEM(opcode));
  return 3;
}


uint8_t subw_x_longmem(uint8_t *opcode){
  mcu_subw(&XH, GET_LONG_MEM_SRC(opcode));
  return 4;
}

uint8_t subw_x_shortoff_sp(uint8_t *opcode){
  mcu_subw(&XH, GET_SHORT_OFF_SP_SRC(opcode));
  return 3;
}

uint8_t subw_y_word(uint8_t *opcode){
  mcu_subw(&YH, GET_LONG_MEM(opcode));
  return 4;
}

uint8_t subw_y_longmem(uint8_t *opcode){
  mcu_subw(&YH, GET_LONG_MEM_SRC(opcode));
  return 4;
}

uint8_t subw_y_shortoff_sp(uint8_t *opcode){
  mcu_subw(&YH, GET_SHORT_OFF_SP_SRC(opcode));
  return 3;
}
#include "SWAPW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define SWAPW_REG(regH)  uint16_t word = SWAP_WORD(getBigEndianWord(&regH)); setBigEndianWord(&regH, word); UPDATE_Z_N_FLAG_FOR_WORD(word);


uint8_t swapw_x(uint8_t *opcode){
  SWAPW_REG(XH);
  return 1;
}

uint8_t swapw_y(uint8_t *opcode){
  SWAPW_REG(YH);
  return 2;
}
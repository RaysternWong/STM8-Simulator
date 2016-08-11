#include "RLWA.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define RLWA(regH,regL)   A = regH; regH = regL; regL = A; UPDATE_Z_N_FLAG_FOR_WORD(getBigEndianWord(&regH))

uint8_t rlwa_x(uint8_t *opcode){
  RLWA(XH, XL) ;
  return 1;
}

uint8_t rlwa_y(uint8_t *opcode){
  RLWA(YH,YL) ;
  return 2;
}
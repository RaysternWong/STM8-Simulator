#include "RRWA.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define RRWA(regH,regL)   A = regL; regL = regH; regH = A; UPDATE_Z_N_FLAG_FOR_WORD(getBigEndianWord(&regH))

uint8_t rrwa_x(uint8_t *opcode){
  RRWA(XH,XL);
  return 1;
}

uint8_t rrwa_y(uint8_t *opcode){
  RRWA(YH,YL);
  return 2;
}
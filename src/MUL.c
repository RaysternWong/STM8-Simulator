#include "MUL.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"



uint8_t mul_x_a(uint8_t *opcode){
  uint16_t result = XL * A;
  SET_X(result);
  return 1;
}

uint8_t mul_y_a(uint8_t *opcode){
  uint16_t result = YL * A;
  SET_Y(result);
  return 1;
}
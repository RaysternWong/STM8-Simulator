#include "POPW.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t popw_x(uint8_t *opcode){
  XH = mcu_pop();
  XL = mcu_pop();
  return 1;
}

uint8_t popw_y(uint8_t *opcode){
  YH = mcu_pop();
  YL = mcu_pop();
  return 2;
}


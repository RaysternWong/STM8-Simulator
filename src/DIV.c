#include "DIV.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"



uint8_t div_x_a(uint8_t *opcode)
{
  mcu_div(&XH);
  return 1;
}

uint8_t div_y_a(uint8_t *opcode)
{
  mcu_div(&YH);
  return 2;
}
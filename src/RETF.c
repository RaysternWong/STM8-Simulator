#include "RETF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t retf(uint8_t *opcode){
  PCE = mcu_pop();
  PCH = mcu_pop();
  PCL = mcu_pop();
  return 1;
}
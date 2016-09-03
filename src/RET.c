#include "RET.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t ret(uint8_t *opcode){
  *pcToLoad = GET_WORD(mcu_pop(),mcu_pop());
  return 1;
}
#include "CALLF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"



uint8_t callf_extmem(uint8_t *opcode){
  uint32_t extmem = GET_EXT_MEM(opcode);
  mcu_callf(extmem, 4);
  return 4;
}

uint8_t callf_longptr_e(uint8_t *opcode){
  uint32_t extmem = GET_LONG_PTR_E(opcode);
  mcu_callf(extmem, 4);
  return 4;
}
#include "JPF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t jpf_extmem(uint8_t *opcode){
  *pcToLoad = GET_EXT_MEM(opcode);
  return 4;
}

uint8_t jpf_longptr_e(uint8_t *opcode){
  *pcToLoad = GET_LONG_PTR_E(opcode);
  return 4;  
}
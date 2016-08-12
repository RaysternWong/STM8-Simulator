#include "BREAK.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"

uint8_t instr_break(uint8_t *opcode){
  Throw(ERR_BREAK);
  return 1;
}
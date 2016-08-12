#include "WFE.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"

uint8_t wfe(uint8_t *opcode){
  Throw(ERR_WFE);
  return 1;
}
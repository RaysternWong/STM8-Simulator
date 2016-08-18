#include "WFI.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"

uint8_t wfi(uint8_t *opcode){
  I0 = 0;
  I1 = 1;
  Throw(ERR_WFI);
  return 1;
}
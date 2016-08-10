#include "HALT.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t halt(uint8_t *opcode){
  I1 = 1;
  I0 = 0;
  return 1;
}
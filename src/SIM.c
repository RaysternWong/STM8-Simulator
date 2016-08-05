#include "SIM.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sim(uint8_t *opcode){
  L1 = 1;
  L0 = 1;
  return 1; 
}
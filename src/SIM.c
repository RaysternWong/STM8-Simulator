#include "SIM.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t sim(uint8_t *opcode){
  I1 = 1;
  I0 = 1;
  return 1; 
}
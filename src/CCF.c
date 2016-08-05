#include "CCF.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t ccf(uint8_t *opcode){
  C = ~C;
  return 1; 
}
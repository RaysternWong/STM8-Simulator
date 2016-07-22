#include "RCF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t rcf(uint8_t *opcode){
  CC = 0;
  V  = 0;
  L1 = 0;
  H  = 0;
  L0 = 0;
  N  = 0;
  Z  = 0;
  C  = 0;
}
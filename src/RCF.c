#include "RCF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t rcf(uint8_t *opcode){
  clearConditionCodeRegister(&(cpu->ccr));
}
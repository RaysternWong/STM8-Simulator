#include "IRET.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t iret(uint8_t *opcode){
  CC  = mcu_pop();
  A   = mcu_pop();
  XH  = mcu_pop();
  XL  = mcu_pop();
  YH  = mcu_pop();
  YL  = mcu_pop();
  *pcToLoad = 0;
  *pcToLoad += mcu_pop() <<16;
  *pcToLoad += mcu_pop() << 8;
  *pcToLoad += mcu_pop();
  
  return 1;
}
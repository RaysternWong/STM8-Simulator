#include "POP.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t pop_a(uint8_t *opcode){
  A = mcu_pop();
  return 1;
}

uint8_t pop_cc(uint8_t *opcode){
  CC = mcu_pop();
  return 1;
}

uint8_t pop_longmem(uint8_t *opcode){
  uint8_t   value  = mcu_pop();
  setValueHoldByLongmem(opcode, value);
  return 3;
}
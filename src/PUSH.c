#include "PUSH.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

/**  Please refer all the definations and marco in MCU_Operation.h
*
*    void mcu_push(uint8_t value) in MCU_Operation.C
*
*    Because it has sharing's use 
*
*/ 

# define NEXT_OP *(++opcode)

uint8_t push_a(uint8_t *opcode){
  mcu_push(A);
  return 1;
}

uint8_t push_cc(uint8_t *opcode){
  mcu_push(CC);
  return 1;
}

uint8_t push_byte(uint8_t *opcode){
  mcu_push(NEXT_OP);
  return 2;
}

uint8_t push_longmem(uint8_t *opcode){
  uint8_t value = getValueHoldByLongmem(opcode);
  mcu_push(value);
  return 3;
}
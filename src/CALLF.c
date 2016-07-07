#include "CALLF.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

void mcu_callF(uint32_t address, uint8_t length)
{
  uint16_t newPC = PC + length;
  SET_PC_WORD(pcPlusLength);
  mcu_push(PCL);
  mcu_push(PCH);
  SET_PC_WORD(address);
}

uint8_t callf_extmem(uint8_t *opcode){
  
}

uint8_t callf_longptr_e(uint8_t *opcode){
  
}
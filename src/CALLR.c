#include "CALLR.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t callr_shortmem(uint8_t *opcode){
  opcode++;
  uint8_t address = MEM_READ_BYTE(*opcode);

  uint16_t newPC = PC_WORD + 2;
  SET_PC_WORD(newPC);
  mcu_push(PCL);
  mcu_push(PCH);

  newPC = PC_WORD + address;

  SET_PC_WORD(newPC);

  return 2;  
}
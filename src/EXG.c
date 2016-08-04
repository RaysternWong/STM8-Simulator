#include "EXG.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t exg_a_xl(uint8_t *opcode){
  EXCHANGE(A,XL);
  return 1; 
}

uint8_t exg_a_yl(uint8_t *opcode){
  EXCHANGE(A,YL);
  return 1;
}

uint8_t exg_a_longmem(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode);
  
  uint8_t temp = A;
  A = MEM_READ_BYTE(longmem);
  MEM_WRITE_BYTE(longmem, temp);
  return 2;
}
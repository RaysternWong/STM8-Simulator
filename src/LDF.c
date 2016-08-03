#include "LDF.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

//-----------------------Load mem to A----------------------------------------


uint8_t ldf_a_extmem(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_EXT_MEM_SRC(opcode));
  return 4;
}

uint8_t ldf_a_extoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_EXT_OFF_X_SRC(opcode));
  return 4;
}

uint8_t ldf_a_extoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_EXT_OFF_Y_SRC(opcode));
  return 5;
}

uint8_t ldf_a_longptr_e_x(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_PTR_E_X_SRC(opcode));
  return 4;
}

uint8_t ldf_a_longptr_e_y(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_PTR_E_Y_SRC(opcode));
  return 4;
}

uint8_t ldf_a_longptr_e(uint8_t *opcode){
  LOAD_BYTE_TO_REG( A, GET_LONG_PTR_E_SRC(opcode));
  return 4;
}

//-----------------------Load A to mem----------------------------------------

uint8_t ldf_a_to_extmem(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_EXT_MEM(opcode), A);
  return 4;
}

uint8_t ldf_a_to_extoff_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_EXT_OFF_X(opcode), A);
  return 4;
}

uint8_t ldf_a_to_extoff_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_EXT_OFF_Y(opcode), A);
  return 5;
}

uint8_t ldf_a_to_longptr_e_x(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_LONG_PTR_E_X(opcode), A);
  return 4;
}

uint8_t ldf_a_to_longptr_e_y(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_LONG_PTR_E_Y(opcode), A);
  return 4;
}

uint8_t ldf_a_to_longptr_e(uint8_t *opcode){
  LOAD_BYTE_TO_MEM( GET_LONG_PTR_E(opcode), A);
  return 4;
}
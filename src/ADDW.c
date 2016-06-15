#include "ADDW.h"
#include <stdint.h>


/**
*  Please refer the folowing instruction in the page 78 of programming manual
*
*   'ht' means hast tag
*    example  addw_x_ht_word(), it means addw x,#$1000
*
*/


uint8_t addw_x_ht_word(uint8_t *opcode){
  opcode++;
  return 3;
}


uint8_t addw_x_longmem(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t addw_x_shortoff_sp(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t addw_y_ht_word(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t addw_y_longmem(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t addw_y_shortoff_sp(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t addw_sp_ht_byte(uint8_t *opcode){
  opcode++; 
  return 2;
}
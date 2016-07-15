#include "ADDW.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t addw_x_word(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t value = combineMostLeastByte( msb , lsb);
  mcu_addw(&XH, &XL, value);
  return 3;
}


uint8_t addw_x_longmem(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = combineMostLeastByte( msb , lsb);

  uint8_t  value    = getValueFromAddress(fullAddr);
  mcu_addw(&XH, &XL, value);
  return 4;
}

uint8_t addw_x_shortoff_sp(uint8_t *opcode){
  opcode++;

  uint16_t sp = combineMostLeastByte( SPH , SPL);
           sp += *opcode;
           
  uint8_t  value =  getValueFromAddress(sp);
  mcu_addw(&XH, &XL, value);
  return 3;
}

uint8_t addw_y_word(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t value = combineMostLeastByte( msb , lsb);
  mcu_addw(&YH, &YL, value);
  return 4;
}

uint8_t addw_y_longmem(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = combineMostLeastByte( msb , lsb);

  uint8_t  value    = getValueFromAddress(fullAddr);
  mcu_addw(&YH, &YL, value);
  return 4;
}

uint8_t addw_y_shortoff_sp(uint8_t *opcode){
  opcode++;

  uint16_t sp = combineMostLeastByte( SPH , SPL);
           sp += *opcode;
           
  uint8_t  value =  getValueFromAddress(sp);
  mcu_addw(&YH, &YL, value);
  return 3;
}

uint8_t addw_sp_byte(uint8_t *opcode){
  opcode++;
  
  mcu_addw(&SPH, &SPL, *opcode);
  return 2;
}
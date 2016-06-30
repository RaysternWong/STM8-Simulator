#include "ADDW.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define A     (cpu->a)           //Accumulator
#define XH    (cpu->xh)           //most significant byte of the X index register  (1 byte)
#define XL    (cpu->xl)           //least significant byte of the X index register (1 byte)
#define YH    (cpu->yh)           //most significant byte of the y index register  (1 byte)
#define YL    (cpu->yl)           //least significant byte of the y index register (1 byte)
#define SPH   (cpu->sph)          //most significant byte of the sph index register  (1 byte)
#define SPL   (cpu->spl)          //least significant byte of the spl index register (1 byte)

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
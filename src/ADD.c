#include "ADD.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t add_a_byte(uint8_t *opcode){
  opcode++;
  mcu_add(*opcode);
  return 2;
}

uint8_t add_a_shortmem(uint8_t *opcode){
  uint8_t value =  getShortmemSrc(opcode);
  mcu_add(value);
  return 2;
}

uint8_t add_a_longmem(uint8_t *opcode){
  uint8_t  value = getlongmemSrc(opcode);
  mcu_add(value);
  return 3;
}

uint8_t add_a_x(uint8_t *opcode){

  uint16_t x     = getBigEndianWord( XH , XL);
  uint8_t  value = MEM_READ_BYTE(x);
  
  mcu_add(value);
  return 1;
}

uint8_t add_a_shortoff_x(uint8_t *opcode){
  opcode++;

  uint16_t x = getBigEndianWord( XH , XL);
           x += *opcode;
  uint8_t  value =  MEM_READ_BYTE(x);
  mcu_add(value);
  return 2;
}

uint8_t add_a_longoff_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = getBigEndianWord( msb , lsb);
  uint16_t x        = getBigEndianWord( XH , XL);
           x       += fullAddr;

  uint8_t  value = MEM_READ_BYTE(x);
  mcu_add(value);
  return 3;
}


uint8_t add_a_y(uint8_t *opcode){
  uint16_t y     = getBigEndianWord( YH , YL);
  uint8_t  value = MEM_READ_BYTE(y);
  
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortoff_y(uint8_t *opcode){
  opcode++;

  uint16_t y = getBigEndianWord( YH , YL);
           y += *opcode;
  uint8_t  value =  MEM_READ_BYTE(y);
  mcu_add(value);
  return 3;
}

uint8_t add_a_longoff_y(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = getBigEndianWord( msb , lsb);
  uint16_t y        = getBigEndianWord( YH , YL);
           y       += fullAddr;

  uint8_t  value = MEM_READ_BYTE(y);
  mcu_add(value);
  return 4;
}

uint8_t add_a_shortoff_sp(uint8_t *opcode){
  opcode++;

  uint16_t sp = getBigEndianWord( SPH , SPL);
           sp += *opcode;
  uint8_t  value =  MEM_READ_BYTE(sp);
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortptr_w(uint8_t *opcode){
  
  uint8_t  value1 =  MEM_READ_BYTE( *(++opcode) );
  uint8_t  value2 =  MEM_READ_BYTE( *opcode + 1 );
  
  uint16_t fullAddr = getBigEndianWord( value1 , value2);
  uint8_t  value    = MEM_READ_BYTE(fullAddr);
  mcu_add(value);

  return 3;
}

uint8_t add_a_longptr_w(uint8_t *opcode){
  
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr1 = getBigEndianWord( msb , lsb);
  
  uint8_t  value1 =  MEM_READ_BYTE( fullAddr1);
  uint8_t  value2 =  MEM_READ_BYTE( fullAddr1 + 1 );
  
  uint16_t fullAddr = getBigEndianWord( value1 , value2);
  uint8_t  value    = MEM_READ_BYTE(fullAddr);
  mcu_add(value);

  return 4;
}

uint8_t add_a_shortptr_w_x(uint8_t *opcode){
  uint8_t  value1 =  MEM_READ_BYTE( *(++opcode) );
  uint8_t  value2 =  MEM_READ_BYTE( *opcode + 1 );
  
  uint16_t fullAddr = getBigEndianWord( value1 , value2);
  uint16_t x        = getBigEndianWord( XH , XL);
           x       += fullAddr;
           
  uint8_t  value    = MEM_READ_BYTE(x);
  mcu_add(value); 
  return 3;
}

uint8_t add_a_longptr_w_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr1 = getBigEndianWord( msb , lsb);
  
  uint8_t  value1 =  MEM_READ_BYTE( fullAddr1);
  uint8_t  value2 =  MEM_READ_BYTE( fullAddr1 + 1 );
  
  uint16_t fullAddr = getBigEndianWord( value1 , value2);
  uint16_t x        = getBigEndianWord( XH , XL);
           x       += fullAddr;
          
  uint8_t  value    = MEM_READ_BYTE(x);
  mcu_add(value); 
  return 4;
}

uint8_t add_a_shortptr_w_y(uint8_t *opcode){
  uint8_t  value1 =  MEM_READ_BYTE( *(++opcode) );
  uint8_t  value2 =  MEM_READ_BYTE( *opcode + 1 );
  
  uint16_t fullAddr = getBigEndianWord( value1 , value2);
  uint16_t y        = getBigEndianWord( YH , YL);
           y       += fullAddr;
           
  uint8_t  value    = MEM_READ_BYTE(y);
  mcu_add(value); 
  return 3;
}





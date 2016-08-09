#include "JRXX.h"
#include <stdint.h>
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t jrc(uint8_t *opcode){
  JRXX( C == 1 );
  return 2;
}

uint8_t jreq(uint8_t *opcode){
  JRXX( Z == 1 );
  return 2;
}

uint8_t jrf(uint8_t *opcode){

  return 2;
}

uint8_t jrh(uint8_t *opcode){
  JRXX( H == 1 );
  return 2;
}

uint8_t jrih(uint8_t *opcode){
 
  return 2;
}

uint8_t jril(uint8_t *opcode){ 

  return 2;
}

uint8_t jrm(uint8_t *opcode){ 
  JRXX( IM == 1 );
  return 2;
}

uint8_t jrmi(uint8_t *opcode){ 
  JRXX( N == 1 );
  return 2;
}

uint8_t jrnc(uint8_t *opcode){
  JRXX( C == 0 );
  return 2;
}

uint8_t jrne(uint8_t *opcode){ 
  JRXX( Z == 0 );
  return 2;
}

uint8_t jrnh(uint8_t *opcode){ 
  JRXX( H == 0 );
  return 2;
}

uint8_t jrnm(uint8_t *opcode){ 
  JRXX( IM == 0 );
  return 2;
}

uint8_t jrnv(uint8_t *opcode){ 
  JRXX( V == 0 );
  return 2;
}

uint8_t jrpl(uint8_t *opcode){ 
  JRXX( N == 0 );
  return 2;
}

uint8_t jrsge(uint8_t *opcode){ 
  JRXX( N ^ V == 0 );
  return 2;
}

uint8_t jrsgt(uint8_t *opcode){ 
  JRXX( ( Z | (N ^ V) ) == 0 );
  return 2;
}

uint8_t jrsle(uint8_t *opcode){
  JRXX( ( Z | (N ^ V) ) == 1 );
  return 2;
}

uint8_t jrslt(uint8_t *opcode){ 
  JRXX( N ^ V == 1 );
  return 2;
}

uint8_t jrt(uint8_t *opcode){ 
  SET_PC( PC + 2 + GET_NEXT_BYTE_OF(opcode) );
  return 2;
}

uint8_t jruge(uint8_t *opcode){ 
  JRXX( C == 0 );
  return 2;
}

uint8_t jrugt(uint8_t *opcode){ 
  JRXX( C == 0 && Z == 0 );
  return 2;
}

uint8_t jrule(uint8_t *opcode){ 
  JRXX( C == 1 && Z == 1 );
  return 2;
}

uint8_t jrult(uint8_t *opcode){
  JRXX( C == 1 );
  return 2;
}

uint8_t jrv  (uint8_t *opcode){
  JRXX( V == 1 );
  return 2;
}
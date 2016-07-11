#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint16_t getBigEndianWord(uint8_t *bytes){
  uint8_t msb = *bytes;
  uint8_t lsb = GET_BYTE(bytes);
  
  return ( (msb<<8) + lsb);
}

uint32_t getBigEndianExt(uint8_t *bytes){
  uint8_t extB = *bytes;
  uint8_t msb  = GET_BYTE(bytes);
  uint8_t lsb  = GET_BYTE(bytes);
  return ( (extB<<16) + (msb<<8) + lsb);
}

void setBigEndianWord(uint8_t *bytes, uint16_t word){
  uint8_t *msb =  bytes;
  uint8_t *lsb =  ++bytes;
  
  *msb = word >> 8;
  *lsb = word & 0x00FF;
}

void setBigEndianExt(uint8_t *bytes, uint32_t extend){
  uint8_t *ext =  bytes;
  uint8_t *msb =  ++bytes;
  uint8_t *lsb =  ++bytes;
  
  *ext = extend >> 16;
  *msb = extend >> 8;
  *lsb = extend & 0x00FF;
}


void setBigEndianMSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte){
  *mostByte  = fullByte >> 8;
}

void setBigEndianLSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte){
  *leastByte = fullByte & 0x00FF;
}

void sp_decrement(void){
  uint16_t stack = SP;
  setBigEndianWord(&SPH, --stack);
}

void sp_increment(void){
  uint16_t stack = SP;
  setBigEndianWord(&SPH, ++stack);  
}

void mcu_push(uint8_t value){
  MEM_WRITE_BYTE(SP,value);
  sp_decrement();
}

uint8_t mcu_pop(void){
  sp_increment();
  uint16_t value = MEM_READ_BYTE(SP);
  return value;
}

void mcu_call(uint16_t address, uint8_t length){
  uint16_t pcPlusLength = PC_WORD + length;
  SET_PC_WORD(pcPlusLength);
  mcu_push(PCL);
  mcu_push(PCH);
  SET_PC_WORD(address);
}

void mcu_add(uint8_t value){
  uint8_t a       = cpu->a;
  uint8_t result  = a + value;
  
  A = result;
  N = R7;
  Z = (result == 0 ? 1 : 0);
  H = A3 & M3 | M3 & _R3 | _R3 & A3;
  C = A7 & M7 | M7 & _R7 | _R7 & A7;
  V = C ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_addw(uint8_t *mostByte, uint8_t *leastByte, uint16_t value){
  uint16_t a  = getBigEndianWord(mostByte);
  uint16_t result = a + value;
  setBigEndianWord( mostByte, result);

  N = R15;
  Z = (result == 0 ? 1 : 0);
  H = A7 & M7 | M7 & _R7 | _R7 & A7;
  C = A15 & M15 | M15 & _R15 | _R15 & A15;
  V = C ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
}


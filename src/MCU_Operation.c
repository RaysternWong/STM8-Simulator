#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint16_t getBigEndianWord(uint8_t mostByte, uint8_t leastByte){
  return ( (mostByte<<8) + leastByte);
}

void setBigEndianWord(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte){
  *mostByte  = fullByte >> 8;
  *leastByte = fullByte & 0x00FF;
}

void setBigEndianMSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte){
  *mostByte  = fullByte >> 8;
}

void setBigEndianLSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte){
  *leastByte = fullByte & 0x00FF;
}

void sp_decrement(void){
  uint16_t stack = SP;
  setBigEndianWord(&SPH, &SPL, --stack);
}

void mcu_push(uint8_t value){
  MEM_WRITE_BYTE(SP,value);
  sp_decrement();
}

void mcu_add(uint8_t value){
  uint8_t a       = cpu->a;
  uint8_t result  = a + value;
  cpu->a          = result;
  
  N = R7;
  Z = (result == 0 ? 1 : 0);
  H = A3 & M3 | M3 & _R3 | _R3 & A3;
  C = A7 & M7 | M7 & _R7 | _R7 & A7;
  V = C ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_addw(uint8_t *mostByte, uint8_t *leastByte, uint16_t value){
  uint16_t a  = getBigEndianWord(*mostByte, *leastByte);
  uint16_t result = a + value;
  setBigEndianWord( mostByte, leastByte, result);

  N = R15;
  Z = (result == 0 ? 1 : 0);
  H = A7 & M7 | M7 & _R7 | _R7 & A7;
  C = A15 & M15 | M15 & _R15 | _R15 & A15;
  V = C ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
}


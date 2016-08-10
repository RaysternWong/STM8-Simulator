#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"

uint16_t getBigEndianWord(uint8_t *bytes){
  uint8_t msb = *bytes;
  uint8_t lsb = GET_NEXT_BYTE_OF(bytes);
  return GET_WORD(msb,lsb);
}

uint32_t getBigEndianExt(uint8_t *bytes){
  uint8_t extb = *bytes;
  uint8_t msb  = INC_THIS(bytes);
  uint8_t lsb  = INC_THIS(bytes);
  return GET_EXT(extb,msb,lsb);
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

void mcu_callf(uint32_t address, uint8_t length){
  uint32_t pc_ext = PC + length;
  SET_PC(pc_ext);
  mcu_push(PCL);
  mcu_push(PCH);
  mcu_push(PCE);
  SET_PC(address);
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

void mcu_adc(uint8_t value){
  uint8_t a       = cpu->a;
  uint8_t result  = a + value + C;
  
  A = result;
  N = R7;
  Z = (result == 0 ? 1 : 0);
  H = A3 & M3 | M3 & _R3 | _R3 & A3;
  C = A7 & M7 | M7 & _R7 | _R7 & A7;
  V = C ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_addw(uint8_t *reg, uint16_t value){
  uint16_t a  = getBigEndianWord(reg);
  uint16_t result = a + value;
  setBigEndianWord( reg, result);

  N = R15;
  Z = (result == 0 ? 1 : 0);
  H = A7 & M7 | M7 & _R7 | _R7 & A7;
  C = A15 & M15 | M15 & _R15 | _R15 & A15;
  V = C ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
}

void mcu_sub(uint8_t value){
  uint8_t a       = cpu->a;
  uint8_t result  = a - value;

  A = result;
  N = R7;
  Z = (result == 0 ? 1 : 0);
  C = _A7 & M7 | _A7 & R7 | A7 & M7 & A7;
  V = (A7 & M7 | A7 & R7 | A7 & M7 & R7) ^ (A6 & M6 | A6 & R6 | A6 & M6 & R6) ;
}

void mcu_sbc(uint8_t value){
  uint8_t a       = cpu->a;
  uint8_t result  = a - value - C;
  
  A = result;
  N = R7;
  Z = (result == 0 ? 1 : 0);
  C = _A7 & M7 | _A7 & R7 | A7 & M7 & A7;
  V = C ^ (_A6 & M6 | _A6 & R6 | A6 & M6 & R6) ;
}

void mcu_subw(uint8_t *reg, uint16_t value){
  uint16_t a  = getBigEndianWord(reg);
  uint16_t result = a - value;
  setBigEndianWord( reg, result);

  N = R15;
  Z = (result == 0 ? 1 : 0);
  H = _A7 & M7 | _A7 & R7 | A7 & M7 & R7;
  C = _A15 & M15 | _A15 & R15 | A15 & M15 & R15;
  V = C ^ ( _A14 & M14 | _A14 & R14 | A14 & M14 & R14);
}

void mcu_neg(uint16_t addr){
  uint8_t result = 0 - MEM_READ_BYTE(addr);
  MEM_WRITE_BYTE( addr, result);
  
  UPDATE_Z_N_FLAG(result);
  C = ~Z;
  V = (result == 0x80 ? 1 : 0);
}

void mcu_inc(uint16_t addr){
  uint8_t a = MEM_READ_BYTE(addr);
  uint8_t value = 1 ;
  uint8_t result =  a + value;
  
  MEM_WRITE_BYTE( addr, result);
  
  UPDATE_Z_N_FLAG(result);
  V = (A7 & M7 | M7 & _R7 | _R7 & A7) ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_dec(uint16_t addr){
  uint8_t a = MEM_READ_BYTE(addr);
  uint8_t value = 1 ;
  uint8_t result =  a - value;
  
  MEM_WRITE_BYTE( addr, result);
  
  UPDATE_Z_N_FLAG(result);
  V = (A7 & M7 | M7 & _R7 | _R7 & A7) ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_div(uint8_t *reg)
{
  if( A == 0){
    C = 1;
    Throw(ERR_DIVIDER_IS_0);
  }
 
  uint16_t regXY      = getBigEndianWord(reg);
  uint16_t quotient   = regXY / A;
  uint8_t  remainder  = regXY % A;
  
  N = 0;
  Z = (quotient == 0 ? 1 : 0);
  H = 0;
  V = 0;
  
  A = remainder;
  setBigEndianWord(reg, quotient);
}

void mcu_cpl(uint16_t addr){
  uint8_t result = 0xFF - MEM_READ_BYTE(addr);
  MEM_WRITE_BYTE( addr, result);
  
  UPDATE_Z_N_FLAG(result);
  C = 1;
}

void mcu_cp(uint8_t dst, uint8_t src){
  uint8_t a = dst;
  uint8_t value = src;
  uint8_t result = a-value;
  SBC_FLAGS_UPDATE(result);
}

void mcu_cpw(uint16_t dst, uint16_t src){
  uint16_t a = dst;
  uint16_t value = src;
  uint16_t result = a-value;
  SUBW_FLAGS_UPDATE(result);
}

#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"

//Short
uint8_t  getShortMemSrc(uint8_t *opcode){
  uint8_t shortMem = GET_NEXT_BYTE_OF(opcode);
  return MEM_READ_BYTE(shortMem);
}

//#define GET_SHORT_MEM_SRC(p)   MEM_READ_BYTE( *( GET_BYTE(p) ) )  

uint8_t getShortOffXSrc(uint8_t *opcode){
  uint16_t x = GET_SHORT_OFF_X(opcode) ;
  return MEM_READ_BYTE(x);
}

uint8_t getShortOffYSrc(uint8_t *opcode){
  uint16_t y = GET_SHORT_OFF_Y(opcode);
  return  MEM_READ_BYTE(y);  
}

uint8_t getShortOffSPSrc(uint8_t *opcode){
  uint16_t sp = GET_SHORT_OFF_SP(opcode);
  return MEM_READ_BYTE(sp);  
}

uint8_t getShortPtrWSrc(uint8_t *opcode){
  uint16_t shortPtrW = GET_SHORT_PTR_W(opcode); 
  return MEM_READ_BYTE(shortPtrW);    
}

uint8_t getShortPtrWXSrc(uint8_t *opcode){
  uint16_t x = GET_SHORT_PTR_W_X(opcode); 
  return MEM_READ_BYTE(x);  
}

uint8_t getShortPtrWYSrc(uint8_t *opcode){
  uint16_t y = GET_SHORT_PTR_W_Y(opcode); 
  return MEM_READ_BYTE(y);  
}

//Long

uint8_t getLongMemSrc(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode);
  return MEM_READ_BYTE(longmem);
}

uint8_t getLongOffXSrc(uint8_t *opcode){
  uint16_t x = GET_LONG_OFF_X(opcode);
  return MEM_READ_BYTE(x);  
}

uint8_t getLongOffYSrc(uint8_t *opcode){
  uint16_t y = GET_LONG_OFF_Y(opcode);
  return MEM_READ_BYTE(y); 
}

uint8_t getLongPtrWSrc(uint8_t *opcode){
  uint16_t word = GET_LONG_PTR_W(opcode); 
  return MEM_READ_BYTE(word);
}


uint8_t getLongPtrWXSrc(uint8_t *opcode){
  uint16_t x = GET_LONG_PTR_W_X(opcode);  
  return MEM_READ_BYTE(x);     
}

void setValueHoldByLongmem(uint8_t *opcode, uint8_t value){
  uint16_t longmem = GET_LONG_MEM(opcode);
  MEM_WRITE_BYTE(longmem, value);
}

//Extend


uint32_t getExtmem(uint8_t *opcode){
  uint32_t extmem  = getBigEndianExt( opcode );
  return extmem;
}

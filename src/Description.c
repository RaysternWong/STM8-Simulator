#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"


uint16_t getlongmem(uint8_t *opcode){
  uint8_t      msb = NEXT_OPCODE;
  uint8_t      lsb = NEXT_OPCODE;
  uint16_t longmem = getBigEndianWord( msb , lsb );
  return longmem;

}

uint8_t getValueHoldByLongmem(uint8_t *opcode){
  uint16_t longmem = getlongmem(opcode);
  uint8_t    value = MEM_READ_BYTE(longmem);
  return value;
}


uint8_t getShortOffX(uint8_t *opcode){
  uint16_t     x = X + NEXT_OPCODE;
  uint8_t  value = MEM_READ_BYTE(x);
  return value;
}

uint8_t getLongOffX(uint8_t *opcode){
  uint16_t longOff = getlongmem(opcode);
  uint16_t       x = X + longOff;
  uint8_t    value = MEM_READ_BYTE(x);  
  
  // printf("%x\n", longOff );
  // printf("%x\n", x );
  return value;  
}

uint8_t getShortOffY(uint8_t *opcode){
  uint16_t     y = Y + NEXT_OPCODE;
  uint8_t  value = MEM_READ_BYTE(y);
  return value;  
  
}

uint8_t getLongOffY(uint8_t *opcode){
  uint16_t longOff = getlongmem(opcode);
  uint16_t       y = Y + longOff;
  uint8_t    value = MEM_READ_BYTE(y);  
  return value;  
}

uint16_t getShortW(uint8_t *opcode){
  opcode++;
  uint8_t  msb =  MEM_READ_BYTE( *opcode );
  uint8_t  lsb =  MEM_READ_BYTE( *opcode + 1 );
  
  uint16_t shortW = getBigEndianWord( msb , lsb);  
  
  // printf("%x\n", msb );
  // printf("%x\n", lsb );
  return shortW;
}

uint8_t getShortPtr(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode); 
  uint8_t  value  = MEM_READ_BYTE(shortW); 
  
  // printf("%x\n", shortW );
  // printf("%x\n", value );
  return value;    
}

uint16_t getLongW(uint8_t *opcode){
  uint16_t longmem = getlongmem(opcode);
  uint16_t longmem_plus1 = longmem + 1;


  uint8_t  msb = MEM_READ_BYTE( longmem);
  uint8_t  lsb = MEM_READ_BYTE( longmem_plus1 );
  
  uint16_t longW = getBigEndianWord( msb , lsb); 
  
  // printf("%x\n", msb );
  // printf("%x\n", lsb );
  return longW;
}

uint8_t getLongPtr(uint8_t *opcode){
  uint16_t longW = getLongW(opcode); 
  uint8_t  value = MEM_READ_BYTE(longW);
  return value;     
}

uint8_t getShortPtrX(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode);
  uint16_t      x = X + shortW; 
  uint8_t   value = MEM_READ_BYTE(x);  
  return value;   
}

uint8_t getLongPtrX(uint8_t *opcode){
  uint16_t longW = getLongW(opcode);
  uint16_t     x = X + longW; 
  uint8_t  value = MEM_READ_BYTE(x);  
  return value;     
  
}

uint8_t getShortPtrY(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode);
  uint16_t      y = Y + shortW; 
  uint8_t   value = MEM_READ_BYTE(y);  
  return value;   
  
}

void setValueHoldByLongmem(uint8_t *opcode, uint8_t value){
  uint16_t longmem = getlongmem(opcode);
  MEM_WRITE_BYTE(longmem, value);
}
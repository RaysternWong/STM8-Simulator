#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"

//Short



uint8_t  getShortmemSrc(uint8_t *opcode){
  opcode++;
  uint8_t src = MEM_READ_BYTE(*opcode);
  return src;
}

uint8_t getShortOffX(uint8_t *opcode){
  uint16_t     x = X + NEXT_OPCODE;
  uint8_t  value = MEM_READ_BYTE(x);
  return value;
}

uint8_t getShortOffY(uint8_t *opcode){
  uint16_t     y = Y + NEXT_OPCODE;
  uint8_t  value = MEM_READ_BYTE(y);
  return value;  
}

uint8_t getShortOffSP(uint8_t *opcode){
  uint16_t     sp = SP + NEXT_OPCODE;
  uint8_t  value = MEM_READ_BYTE(sp);
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
uint8_t getShortPtrW(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode); 
  uint8_t  value  = MEM_READ_BYTE(shortW); 
  
  // printf("%x\n", shortW );
  // printf("%x\n", value );
  return value;    
}

uint8_t getShortPtrX(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode);
  uint16_t      x = X + shortW; 
  uint8_t   value = MEM_READ_BYTE(x);  
  
  //printf("%x\n", x );
  return value;   
}

uint8_t getShortPtrY(uint8_t *opcode){
  uint16_t shortW = getShortW(opcode);
  uint16_t      y = Y + shortW; 
  uint8_t   value = MEM_READ_BYTE(y);  
  return value;   
}

//Long

uint16_t getlongmem(uint8_t *opcode){
  uint8_t      msb = NEXT_OPCODE;
  uint8_t      lsb = NEXT_OPCODE;
  uint16_t longmem = getBigEndianWord( msb , lsb );
  return longmem;
}

uint8_t getlongmemSrc(uint8_t *opcode){
  uint16_t longmem = getlongmem(opcode);
  uint8_t    value = MEM_READ_BYTE(longmem);
  return value;
}


//Extend


uint32_t getExtmem(uint8_t *opcode){
  uint8_t      ext = NEXT_OPCODE;
  uint8_t      msb = NEXT_OPCODE;
  uint8_t      lsb = NEXT_OPCODE;
  uint32_t extmem  = getBigEndianExt( ext, msb , lsb );
  return extmem;
}







uint8_t getLongOffX(uint8_t *opcode){
  uint16_t longOff = getlongmem(opcode);
  uint16_t       x = X + longOff;
  uint8_t    value = MEM_READ_BYTE(x);  
  
  // printf("%x\n", longOff );
  // printf("%x\n", x );
  return value;  
}



uint8_t getLongOffY(uint8_t *opcode){
  uint16_t longOff = getlongmem(opcode);
  uint16_t       y = Y + longOff;
  uint8_t    value = MEM_READ_BYTE(y);  
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

uint32_t getLongE(uint8_t *opcode){
  uint16_t longmem = getlongmem(opcode);
  uint16_t longmem_plus1 = longmem + 1;
  uint16_t longmem_plus2 = longmem + 2;


  uint8_t  ext = MEM_READ_BYTE( longmem);
  uint8_t  msb = MEM_READ_BYTE( longmem_plus1 );
  uint8_t  lsb = MEM_READ_BYTE( longmem_plus2 );
  
  uint32_t longE = getBigEndianExt( ext, msb , lsb); 
  
  return longE;
}

uint8_t getLongPtr(uint8_t *opcode){
  uint16_t longW = getLongW(opcode); 
  uint8_t  value = MEM_READ_BYTE(longW);
  return value;     
}

uint8_t getLongPtrE(uint8_t *opcode){
  uint32_t longE = getLongE(opcode); 
  uint8_t  value = MEM_READ_BYTE(longE);
  return value;  
}


uint8_t getLongPtrX(uint8_t *opcode){
  uint16_t longW = getLongW(opcode);
  uint16_t     x = X + longW; 
  uint8_t  value = MEM_READ_BYTE(x);  
  return value;     
  
}



void setValueHoldByLongmem(uint8_t *opcode, uint8_t value){
  uint16_t longmem = getlongmem(opcode);
  MEM_WRITE_BYTE(longmem, value);
}
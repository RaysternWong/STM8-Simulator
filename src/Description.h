#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <stdio.h>


#define GET_BYTE(p)            ( *(++p) ) 
#define GET_SHORT_MEM_SRC(p)   MEM_READ_BYTE( *( GET_BYTE(p) ) )  


#define GET_SHORT_OFF_X(p)   (X + GET_BYTE(p) )




//Short
uint8_t   getShortMemSrc(uint8_t *opcode);

uint8_t   getShortOffXSrc(uint8_t *opcode);
uint8_t   getShortOffYSrc(uint8_t *opcode);
uint8_t   getShortOffSPSrc(uint8_t *opcode);
uint16_t  getShortW   (uint8_t *opcode);
uint8_t   getShortPtrW(uint8_t *opcode);
uint8_t   getShortPtrX(uint8_t *opcode);
uint8_t   getShortPtrY(uint8_t *opcode);



//Long
uint16_t  getlongmem(uint8_t *opcode);
uint8_t   getlongmemSrc(uint8_t *opcode);
uint8_t   getLongOffX(uint8_t *opcode);
uint8_t   getLongOffY(uint8_t *opcode);
uint8_t   getLongPtr(uint8_t *opcode);
uint16_t  getLongW(uint8_t *opcode);
uint8_t   getLongPtrX(uint8_t *opcode);

uint32_t  getLongE(uint8_t *opcode);
uint8_t   getLongPtrE(uint8_t *opcode);

//Extend

uint32_t  getExtmem(uint8_t *opcode);











void     setValueHoldByLongmem(uint8_t *opcode, uint8_t value);

#endif // Description_H

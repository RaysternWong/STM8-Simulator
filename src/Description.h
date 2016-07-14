#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <stdio.h>


#define GET_BYTE(p)            ( *(++p) ) 
#define GET_SHORT_MEM_SRC(p)   MEM_READ_BYTE( *( GET_BYTE(p) ) )  
//  MEM_READ_BYTE(addr)  memoryTable[addr/0x100](MEM_READ, addr, 1, 0)

#define GET_SHORT_OFF_X(p)   (X + GET_BYTE(p) )
#define GET_SHORT_OFF_Y(p)   (Y + GET_BYTE(p) )
#define GET_SHORT_OFF_SP(p)  (SP + GET_BYTE(p) )
#define GET_SHORT_PTR_W(p)   ( getBigEndianWordFromAddress(GET_BYTE(p)) )
#define GET_SHORT_PTR_W_X(p)  ( X + GET_SHORT_PTR_W(p) )
#define GET_SHORT_PTR_W_Y(p)  ( Y + GET_SHORT_PTR_W(p) )


#define GET_LONG_MEM(p)     getBigEndianWord(++p)
#define GET_LONG_OFF_X(p)   X + GET_LONG_MEM(p) 
#define GET_LONG_OFF_Y(p)   Y + GET_LONG_MEM(p) 
#define GET_LONG_PTR_W(p)   getBigEndianWordFromAddress(GET_LONG_MEM(p)) 
#define GET_LONG_PTR_E(p)   getBigEndianExtFromAddress(GET_LONG_MEM(p)) 
#define GET_LONG_PTR_W_X(p)   X + getBigEndianWordFromAddress(GET_LONG_MEM(p)) 

//Short
uint8_t   getShortMemSrc(uint8_t *opcode);

uint8_t   getShortOffXSrc(uint8_t *opcode);
uint8_t   getShortOffYSrc(uint8_t *opcode);
uint8_t   getShortOffSPSrc(uint8_t *opcode);
uint8_t   getShortPtrWSrc(uint8_t *opcode);
uint8_t   getShortPtrWXSrc(uint8_t *opcode);
uint8_t   getShortPtrWYSrc(uint8_t *opcode);



//Long

uint8_t   getLongMemSrc(uint8_t *opcode);
uint8_t   getLongOffXSrc(uint8_t *opcode);
uint8_t   getLongOffYSrc(uint8_t *opcode);
uint8_t   getLongPtrWSrc(uint8_t *opcode);
uint8_t   getLongPtrWXSrc(uint8_t *opcode);



//Extend

uint32_t  getExtmem(uint8_t *opcode);











void     setValueHoldByLongmem(uint8_t *opcode, uint8_t value);

#endif // Description_H

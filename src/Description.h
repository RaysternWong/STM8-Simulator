#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <stdio.h>

#define INC_THIS(p)            (*(++p))
#define GET_NEXT_BYTE_OF(p)    (*(1+p))
#define GET_WORD(p)            getBigEndianWord(++p)     // GETWORD is same as GET_LONG_MEM


#define GET_SHORT_MEM(p)      (*(1+p))
#define GET_SHORT_OFF_X(p)    (X + GET_SHORT_MEM(p) )
#define GET_SHORT_OFF_Y(p)    (Y + GET_SHORT_MEM(p) )
#define GET_SHORT_OFF_SP(p)   (SP + GET_SHORT_MEM(p) )
#define GET_SHORT_PTR_W(p)    (getBigEndianWordFromAddress(GET_SHORT_MEM(p)) )
#define GET_SHORT_PTR_W_X(p)  (X + GET_SHORT_PTR_W(p) )
#define GET_SHORT_PTR_W_Y(p)  (Y + GET_SHORT_PTR_W(p) )


#define GET_SHORT_MEM_SRC(p)      MEM_READ_BYTE( GET_SHORT_MEM(p)    ) 
#define GET_SHORT_OFF_X_SRC(p)    MEM_READ_BYTE( GET_SHORT_OFF_X(p)  ) 
#define GET_SHORT_OFF_Y_SRC(p)    MEM_READ_BYTE( GET_SHORT_OFF_Y(p)  ) 
#define GET_SHORT_OFF_SP_SRC(p)   MEM_READ_BYTE( GET_SHORT_OFF_SP(p) ) 
#define GET_SHORT_PTR_W_SRC(p)    MEM_READ_BYTE( GET_SHORT_PTR_W(p)  ) 
#define GET_SHORT_PTR_W_X_SRC(p)  MEM_READ_BYTE( GET_SHORT_PTR_W_X(p)) 
#define GET_SHORT_PTR_W_Y_SRC(p)  MEM_READ_BYTE( GET_SHORT_PTR_W_Y(p)) 


#define GET_LONG_MEM(p)     (getBigEndianWord(1+p) ) 
#define GET_LONG_OFF_X(p)   (X + GET_LONG_MEM(p) ) 
#define GET_LONG_OFF_Y(p)   (Y + GET_LONG_MEM(p) )
#define GET_LONG_OFF_SP(p)  (SP + GET_LONG_MEM(p) ) 
#define GET_LONG_PTR_W(p)   (getBigEndianWordFromAddress(GET_LONG_MEM(p)) )
#define GET_LONG_PTR_E(p)   (getBigEndianExtFromAddress(GET_LONG_MEM(p)) )
#define GET_LONG_PTR_W_X(p) (X + GET_LONG_PTR_W(p) )
#define GET_LONG_PTR_W_Y(p) (Y + GET_LONG_PTR_W(p) ) 

#define GET_LONG_MEM_SRC(p)     MEM_READ_BYTE( GET_LONG_MEM(p)    )  
#define GET_LONG_OFF_X_SRC(p)   MEM_READ_BYTE( GET_LONG_OFF_X(p)  )  
#define GET_LONG_OFF_Y_SRC(p)   MEM_READ_BYTE( GET_LONG_OFF_Y(p)  ) 
#define GET_LONG_OFF_SP_SRC(p)  MEM_READ_BYTE( GET_LONG_OFF_SP(p) )  
#define GET_LONG_PTR_W_SRC(p)   MEM_READ_BYTE( GET_LONG_PTR_W(p)  ) 
#define GET_LONG_PTR_E_SRC(p)   MEM_READ_BYTE( GET_LONG_PTR_E(p)  ) 
#define GET_LONG_PTR_W_X_SRC(p)  MEM_READ_BYTE( GET_LONG_PTR_W_X(p)) 
#define GET_LONG_PTR_W_Y_SRC(p)  MEM_READ_BYTE( GET_LONG_PTR_W_Y(p)) 


#define GET_EXT_MEM(p)     getBigEndianExt(1+p)

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

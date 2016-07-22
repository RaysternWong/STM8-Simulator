#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include <stdio.h>

#define INC_THIS(p)            (*(++p))
#define GET_NEXT_BYTE_OF(p)    (*(1+p))
#define GET_WORD(p)            (getBigEndianWord(1+p) )     // GETWORD is same as GET_LONG_MEM


//-------------------------------------------SHORT-------------------------------------------------------

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

//-------------------------------------------LONG-------------------------------------------------------

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

#define SET_LONG_MEM_SRC(p, value)     MEM_WRITE_BYTE( GET_LONG_MEM(p), value)  

//-------------------------------------------EXTEND-------------------------------------------------------

#define GET_EXT_MEM(p)     getBigEndianExt(1+p)



#endif // Description_H

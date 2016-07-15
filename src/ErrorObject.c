#include <malloc.h>
#include <stdarg.h>
#include "ErrorObject.h"
#include "CException.h"


/**
 *  ThrowError generate a errorObj that stored the detail of errObj 
 *  This function stored error details as shown
 *         __________
 *        [ errorMsg ]
 *        [errorCode ] 
 *
 *
 *  Eg,
 *  Calling function by
 *  ThrowError("This operator is undefined!", ERR_UNDEFINED_OPERATOR)
 *		   _____________________________
 *        ["This operator is undefined!"]
 *        [   ERR_UNDEFINED_OPERATOR    ]
 */
void ThrowError(ErrorCode errCode, char *message, ...){
  ErrorObject* errObj = malloc(sizeof(ErrorObject));
  char *messageBuffer;
  int strLength;

  va_list args;
  va_start(args, message);
  strLength     = vsnprintf(messageBuffer, 0, message, args);
  messageBuffer = malloc(strLength + 1);
  vsprintf(messageBuffer, message, args);

  errObj->errorMsg  = messageBuffer;
  errObj->errorCode = errCode;
  
  va_end(args);
  Throw(errObj);
}

void freeError(ErrorObject *errObj){
  free(errObj);
}

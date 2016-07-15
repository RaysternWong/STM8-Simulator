#ifndef ErrorObject_H
#define ErrorObject_H

typedef enum{	
  ERR_INSTRUCTION_NOT_IN_TABLE,
  ERR_DIVIDER_IS_0,
  ERR_OVERFLOW_OF_PC,					
  ERR_UNINITIALIZED_ADDRESS							
} ErrorCode;


typedef struct{
  char *errorMsg;									//errorMsg give a message about the error.
  ErrorCode errorCode;								//ErrorCode is to show the type of error that throw in the function.
} ErrorObject;

void freeError(ErrorObject *errObj);
void ThrowError(ErrorCode errCode, char *message, ...);

#endif // ErrorObject_H


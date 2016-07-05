#include "printfFunction.h"


void printfLongmem(uint8_t *opcode){
  printf("%x\n", getlongmem( opcode) );
}

void printflongmemValue(uint8_t *opcode){
  printf("%x\n", getValueHoldByLongmem( opcode) );
}
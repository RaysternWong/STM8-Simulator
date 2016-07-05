#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint16_t getlongmem(uint8_t *opcode);
uint8_t  getValueHoldByLongmem(uint8_t *opcode);


#endif // Description_H

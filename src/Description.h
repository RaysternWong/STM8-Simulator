#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint16_t getlongmem(uint8_t *opcode);
uint8_t  getValueHoldByLongmem(uint8_t *opcode);
void     setValueHoldByLongmem(uint8_t *opcode, uint8_t value);

#endif // Description_H

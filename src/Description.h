#ifndef Description_H
#define Description_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint16_t getlongmem(uint8_t *opcode);
uint32_t getExtmem(uint8_t *opcode);
uint8_t  getValueHoldByLongmem(uint8_t *opcode);
uint8_t getShortOffX(uint8_t *opcode);
uint8_t getLongOffX(uint8_t *opcode);
uint8_t getShortOffY(uint8_t *opcode);
uint8_t getLongOffY(uint8_t *opcode);

uint16_t getShortW(uint8_t *opcode);
uint16_t getLongW(uint8_t *opcode);
uint32_t getLongE(uint8_t *opcode);


uint8_t getShortPtr(uint8_t *opcode);
uint8_t getLongPtr(uint8_t *opcode);

uint8_t getLongPtrE(uint8_t *opcode);

uint8_t getShortPtrX(uint8_t *opcode);
uint8_t getLongPtrX(uint8_t *opcode);
uint8_t getShortPtrY(uint8_t *opcode);

void     setValueHoldByLongmem(uint8_t *opcode, uint8_t value);

#endif // Description_H

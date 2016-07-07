#ifndef POP_H
#define POP_H
#include <stdint.h>

uint8_t pop_a       (uint8_t *opcode);
uint8_t pop_cc      (uint8_t *opcode);
uint8_t pop_longmem (uint8_t *opcode);


#endif // POP_H

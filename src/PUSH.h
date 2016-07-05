#ifndef PUSH_H
#define PUSH_H
#include <stdint.h>

uint8_t push_a        (uint8_t *opcode);
uint8_t push_cc       (uint8_t *opcode);
uint8_t push_byte     (uint8_t *opcode);
uint8_t push_longmem  (uint8_t *opcode);

#endif // PUSH_H

#ifndef NEG_H
#define NEG_H
#include <stdint.h>

uint8_t neg_a           (uint8_t *opcode);
uint8_t neg_shortmem    (uint8_t *opcode);
uint8_t neg_longmem     (uint8_t *opcode);
uint8_t neg_x           (uint8_t *opcode);
uint8_t neg_shortoff_x  (uint8_t *opcode);
uint8_t neg_longoff_x   (uint8_t *opcode);
uint8_t neg_y           (uint8_t *opcode);
uint8_t neg_shortoff_y  (uint8_t *opcode);
uint8_t neg_longoff_y   (uint8_t *opcode);
uint8_t neg_shortoff_sp (uint8_t *opcode);
uint8_t neg_shortptr_w  (uint8_t *opcode);


#endif // NEG_H

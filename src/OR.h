#ifndef OR_H
#define OR_H
#include <stdint.h>

uint8_t or_a_byte        (uint8_t *opcode);
uint8_t or_a_shortmem    (uint8_t *opcode);
uint8_t or_a_longmem     (uint8_t *opcode);
uint8_t or_a_x           (uint8_t *opcode);
uint8_t or_a_shortoff_x  (uint8_t *opcode);
uint8_t or_a_longoff_x   (uint8_t *opcode);
uint8_t or_a_y           (uint8_t *opcode);
uint8_t or_a_shortoff_y  (uint8_t *opcode);
uint8_t or_a_longoff_y   (uint8_t *opcode);
uint8_t or_a_shortoff_sp (uint8_t *opcode);
uint8_t or_a_shortptr_w  (uint8_t *opcode);
uint8_t or_a_longptr_w   (uint8_t *opcode);
uint8_t or_a_shortptr_w_x(uint8_t *opcode);
uint8_t or_a_longptr_w_x (uint8_t *opcode);
uint8_t or_a_shortptr_w_y(uint8_t *opcode);


#endif // OR_H

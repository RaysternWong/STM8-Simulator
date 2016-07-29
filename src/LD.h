#ifndef LD_H
#define LD_H
#include <stdint.h>

uint8_t ld_a_byte        (uint8_t *opcode);
uint8_t ld_a_shortmem    (uint8_t *opcode);
uint8_t ld_a_longmem     (uint8_t *opcode);
uint8_t ld_a_x           (uint8_t *opcode);
uint8_t ld_a_shortoff_x  (uint8_t *opcode);
uint8_t ld_a_longoff_x   (uint8_t *opcode);
uint8_t ld_a_y           (uint8_t *opcode);
uint8_t ld_a_shortoff_y  (uint8_t *opcode);
uint8_t ld_a_longoff_y   (uint8_t *opcode);
uint8_t ld_a_shortoff_sp (uint8_t *opcode);
uint8_t ld_a_shortptr_w  (uint8_t *opcode);
uint8_t ld_a_longptr_w   (uint8_t *opcode);
uint8_t ld_a_shortptr_w_x(uint8_t *opcode);
uint8_t ld_a_longptr_w_x (uint8_t *opcode);
uint8_t ld_a_shortptr_w_y(uint8_t *opcode);

#endif // LD_H

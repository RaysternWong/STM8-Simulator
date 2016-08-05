#ifndef TNZ_H
#define TNZ_H
#include <stdint.h>

uint8_t tnz_a           (uint8_t *opcode);
uint8_t tnz_shortmem    (uint8_t *opcode);
uint8_t tnz_longmem     (uint8_t *opcode);
uint8_t tnz_x           (uint8_t *opcode);
uint8_t tnz_shortoff_x  (uint8_t *opcode);
uint8_t tnz_longoff_x   (uint8_t *opcode);
uint8_t tnz_y           (uint8_t *opcode);
uint8_t tnz_shortoff_y  (uint8_t *opcode);
uint8_t tnz_longoff_y   (uint8_t *opcode);
uint8_t tnz_shortoff_sp (uint8_t *opcode);
uint8_t tnz_shortptr_w  (uint8_t *opcode);
uint8_t tnz_longptr_w   (uint8_t *opcode);
uint8_t tnz_shortptr_w_x(uint8_t *opcode);
uint8_t tnz_longptr_w_x (uint8_t *opcode);
uint8_t tnz_shortptr_w_y(uint8_t *opcode);

#endif // TNZ_H

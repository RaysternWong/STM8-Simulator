#ifndef RLC_H
#define RLC_H
#include <stdint.h>

uint8_t rlc_a           (uint8_t *opcode);
uint8_t rlc_shortmem    (uint8_t *opcode);
uint8_t rlc_longmem     (uint8_t *opcode);
uint8_t rlc_x           (uint8_t *opcode);
uint8_t rlc_shortoff_x  (uint8_t *opcode);
uint8_t rlc_longoff_x   (uint8_t *opcode);
uint8_t rlc_y           (uint8_t *opcode);
uint8_t rlc_shortoff_y  (uint8_t *opcode);
uint8_t rlc_longoff_y   (uint8_t *opcode);
uint8_t rlc_shortoff_sp (uint8_t *opcode);
uint8_t rlc_shortptr_w  (uint8_t *opcode);
uint8_t rlc_longptr_w   (uint8_t *opcode);
uint8_t rlc_shortptr_w_x(uint8_t *opcode);
uint8_t rlc_longptr_w_x (uint8_t *opcode);
uint8_t rlc_shortptr_w_y(uint8_t *opcode);

#endif // RLC_H

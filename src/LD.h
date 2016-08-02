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

uint8_t ld_a_to_shortmem    (uint8_t *opcode);
uint8_t ld_a_to_longmem     (uint8_t *opcode);
uint8_t ld_a_to_x           (uint8_t *opcode);
uint8_t ld_a_to_shortoff_x  (uint8_t *opcode);
uint8_t ld_a_to_longoff_x   (uint8_t *opcode);
uint8_t ld_a_to_y           (uint8_t *opcode);
uint8_t ld_a_to_shortoff_y  (uint8_t *opcode);
uint8_t ld_a_to_longoff_y   (uint8_t *opcode);
uint8_t ld_a_to_shortoff_sp (uint8_t *opcode);
uint8_t ld_a_to_shortptr_w  (uint8_t *opcode);
uint8_t ld_a_to_longptr_w   (uint8_t *opcode);
uint8_t ld_a_to_shortptr_w_x(uint8_t *opcode);
uint8_t ld_a_to_longptr_w_x (uint8_t *opcode);
uint8_t ld_a_to_shortptr_w_y(uint8_t *opcode);

uint8_t ld_xl_a(uint8_t *opcode);
uint8_t ld_a_xl(uint8_t *opcode);
uint8_t ld_yl_a(uint8_t *opcode);
uint8_t ld_a_yl(uint8_t *opcode);
uint8_t ld_xh_a(uint8_t *opcode);
uint8_t ld_a_xh(uint8_t *opcode);
uint8_t ld_yh_a(uint8_t *opcode);
uint8_t ld_a_yh(uint8_t *opcode);

#endif // LD_H

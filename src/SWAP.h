#ifndef SWAP_H
#define SWAP_H
#include <stdint.h>

uint8_t swap_a           (uint8_t *opcode);
uint8_t swap_shortmem    (uint8_t *opcode);
uint8_t swap_longmem     (uint8_t *opcode);
uint8_t swap_x           (uint8_t *opcode);
uint8_t swap_shortoff_x  (uint8_t *opcode);
uint8_t swap_longoff_x   (uint8_t *opcode);
uint8_t swap_y           (uint8_t *opcode);
uint8_t swap_shortoff_y  (uint8_t *opcode);
uint8_t swap_longoff_y   (uint8_t *opcode);
uint8_t swap_shortoff_sp (uint8_t *opcode);
uint8_t swap_shortptr_w  (uint8_t *opcode);
uint8_t swap_longptr_w   (uint8_t *opcode);
uint8_t swap_shortptr_w_x(uint8_t *opcode);
uint8_t swap_longptr_w_x (uint8_t *opcode);
uint8_t swap_shortptr_w_y(uint8_t *opcode);


#endif // SWAP_H

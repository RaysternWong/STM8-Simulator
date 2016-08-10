#ifndef SLL_H
#define SLL_H
#include <stdint.h>

uint8_t sll_a           (uint8_t *opcode);
uint8_t sll_shortmem    (uint8_t *opcode);
uint8_t sll_longmem     (uint8_t *opcode);
uint8_t sll_x           (uint8_t *opcode);
uint8_t sll_shortoff_x  (uint8_t *opcode);
uint8_t sll_longoff_x   (uint8_t *opcode);
uint8_t sll_y           (uint8_t *opcode);
uint8_t sll_shortoff_y  (uint8_t *opcode);
uint8_t sll_longoff_y   (uint8_t *opcode);
uint8_t sll_shortoff_sp (uint8_t *opcode);
uint8_t sll_shortptr_w  (uint8_t *opcode);
uint8_t sll_longptr_w   (uint8_t *opcode);
uint8_t sll_shortptr_w_x(uint8_t *opcode);
uint8_t sll_longptr_w_x (uint8_t *opcode);
uint8_t sll_shortptr_w_y(uint8_t *opcode);

#endif // SLL_H

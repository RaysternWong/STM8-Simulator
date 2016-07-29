#ifndef INC_H
#define INC_H
#include <stdint.h>

uint8_t inc_a           (uint8_t *opcode);
uint8_t inc_shortmem    (uint8_t *opcode);
uint8_t inc_longmem     (uint8_t *opcode);
uint8_t inc_x           (uint8_t *opcode);
uint8_t inc_shortoff_x  (uint8_t *opcode);
uint8_t inc_longoff_x   (uint8_t *opcode);
uint8_t inc_y           (uint8_t *opcode);
uint8_t inc_shortoff_y  (uint8_t *opcode);
uint8_t inc_longoff_y   (uint8_t *opcode);
uint8_t inc_shortoff_sp (uint8_t *opcode);
uint8_t inc_shortptr_w  (uint8_t *opcode);
uint8_t inc_longptr_w   (uint8_t *opcode);
uint8_t inc_shortptr_w_x(uint8_t *opcode);
uint8_t inc_longptr_w_x (uint8_t *opcode);
uint8_t inc_shortptr_w_y(uint8_t *opcode);

#endif // INC_H

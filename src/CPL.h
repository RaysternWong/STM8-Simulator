#ifndef CPL_H
#define CPL_H
#include <stdint.h>

uint8_t cpl_a           (uint8_t *opcode);
uint8_t cpl_shortmem    (uint8_t *opcode);
uint8_t cpl_longmem     (uint8_t *opcode);
uint8_t cpl_x           (uint8_t *opcode);
uint8_t cpl_shortoff_x  (uint8_t *opcode);
uint8_t cpl_longoff_x   (uint8_t *opcode);
uint8_t cpl_y           (uint8_t *opcode);
uint8_t cpl_shortoff_y  (uint8_t *opcode);
uint8_t cpl_longoff_y   (uint8_t *opcode);
uint8_t cpl_shortoff_sp (uint8_t *opcode);
uint8_t cpl_shortptr_w  (uint8_t *opcode);
uint8_t cpl_longptr_w   (uint8_t *opcode);
uint8_t cpl_shortptr_w_x(uint8_t *opcode);
uint8_t cpl_longptr_w_x (uint8_t *opcode);
uint8_t cpl_shortptr_w_y(uint8_t *opcode);

#endif // CPL_H

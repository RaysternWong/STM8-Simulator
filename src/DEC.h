#ifndef DEC_H
#define DEC_H
#include <stdint.h>

uint8_t dec_a           (uint8_t *opcode);
uint8_t dec_shortmem    (uint8_t *opcode);
uint8_t dec_longmem     (uint8_t *opcode);
uint8_t dec_x           (uint8_t *opcode);
uint8_t dec_shortoff_x  (uint8_t *opcode);
uint8_t dec_longoff_x   (uint8_t *opcode);
uint8_t dec_y           (uint8_t *opcode);
uint8_t dec_shortoff_y  (uint8_t *opcode);
uint8_t dec_longoff_y   (uint8_t *opcode);
uint8_t dec_shortoff_sp (uint8_t *opcode);
uint8_t dec_shortptr_w  (uint8_t *opcode);
uint8_t dec_longptr_w   (uint8_t *opcode);
uint8_t dec_shortptr_w_x(uint8_t *opcode);
uint8_t dec_longptr_w_x (uint8_t *opcode);
uint8_t dec_shortptr_w_y(uint8_t *opcode);

#endif // DEC_H

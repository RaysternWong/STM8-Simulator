#ifndef JP_H
#define JP_H
#include <stdint.h>

uint8_t jp_longmem      (uint8_t *opcode);
uint8_t jp_x            (uint8_t *opcode);
uint8_t jp_shortoff_x   (uint8_t *opcode);
uint8_t jp_longoff_x    (uint8_t *opcode);
uint8_t jp_y            (uint8_t *opcode);
uint8_t jp_shortoff_y   (uint8_t *opcode);
uint8_t jp_longoff_y    (uint8_t *opcode);
uint8_t jp_shortptr_w   (uint8_t *opcode);
uint8_t jp_longptr_w    (uint8_t *opcode);
uint8_t jp_shortptr_w_x (uint8_t *opcode);
uint8_t jp_longptr_w_x  (uint8_t *opcode);
uint8_t jp_shortptr_w_y (uint8_t *opcode);

#endif // JP_H

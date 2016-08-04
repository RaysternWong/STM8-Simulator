#ifndef CLR_H
#define CLR_H
#include <stdint.h>

uint8_t clr_a           (uint8_t *opcode);
uint8_t clr_shortmem    (uint8_t *opcode);
uint8_t clr_longmem     (uint8_t *opcode);
uint8_t clr_x           (uint8_t *opcode);
uint8_t clr_shortoff_x  (uint8_t *opcode);
uint8_t clr_longoff_x   (uint8_t *opcode);
uint8_t clr_y           (uint8_t *opcode);
uint8_t clr_shortoff_y  (uint8_t *opcode);
uint8_t clr_longoff_y   (uint8_t *opcode);
uint8_t clr_shortoff_sp (uint8_t *opcode);
uint8_t clr_shortptr_w  (uint8_t *opcode);
uint8_t clr_longptr_w   (uint8_t *opcode);
uint8_t clr_shortptr_w_x(uint8_t *opcode);
uint8_t clr_longptr_w_x (uint8_t *opcode);
uint8_t clr_shortptr_w_y(uint8_t *opcode);


#endif // CLR_H

#ifndef CALL_H
#define CALL_H
#include <stdint.h>

uint8_t call_longmem      (uint8_t *opcode);
uint8_t call_x            (uint8_t *opcode);
uint8_t call_shortoff_x   (uint8_t *opcode);
uint8_t call_longoff_x    (uint8_t *opcode);
uint8_t call_y            (uint8_t *opcode);
uint8_t call_shortoff_y   (uint8_t *opcode);
uint8_t call_longoff_y    (uint8_t *opcode);
uint8_t call_shortptr_w   (uint8_t *opcode);
uint8_t call_longptr_w    (uint8_t *opcode);
uint8_t call_shortptr_w_x (uint8_t *opcode);
uint8_t call_longptr_w_x  (uint8_t *opcode);
uint8_t call_shortptr_w_y (uint8_t *opcode);


#endif // CALL_H

#ifndef CALL_H
#define CALL_H
#include <stdint.h>


uint8_t call_a_longmem     (uint8_t *opcode);
uint8_t call_a_x           (uint8_t *opcode);
uint8_t call_a_shortoff_x  (uint8_t *opcode);
uint8_t call_a_longoff_x   (uint8_t *opcode);
uint8_t call_a_y           (uint8_t *opcode);
uint8_t call_a_shortoff_y  (uint8_t *opcode);
uint8_t call_a_longoff_y   (uint8_t *opcode);
uint8_t call_a_shortptr_w  (uint8_t *opcode);
uint8_t call_a_longptr_w   (uint8_t *opcode);
uint8_t call_a_shortptr_w_x(uint8_t *opcode);
uint8_t call_a_longptr_w_x (uint8_t *opcode);
uint8_t call_a_shortptr_w_y(uint8_t *opcode);


#endif // CALL_H

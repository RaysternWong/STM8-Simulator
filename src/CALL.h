#ifndef CALL_H
#define CALL_H
#include <stdint.h>


uint8_t call_longmem     (uint8_t *opcode);
uint8_t call_x           (uint8_t *opcode);
uint8_t call_shortoff_x  (uint8_t *opcode);
uint8_t call_longoff_x   (uint8_t *opcode);
uint8_t call_y           (uint8_t *opcode);
uint8_t call_shortoff_y  (uint8_t *opcode);
uint8_t call_longoff_y   (uint8_t *opcode);
uint8_t call_shortptr    (uint8_t *opcode);
uint8_t call_longptr     (uint8_t *opcode);
uint8_t call_shortptr_x(uint8_t *opcode);
uint8_t call_longptr_x (uint8_t *opcode);
uint8_t call_shortptr_y(uint8_t *opcode);


#endif // CALL_H

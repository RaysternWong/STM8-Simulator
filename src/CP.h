#ifndef CP_H
#define CP_H
#include <stdint.h>

uint8_t cp_a_byte        (uint8_t *opcode);
uint8_t cp_a_shortmem    (uint8_t *opcode);
uint8_t cp_a_longmem     (uint8_t *opcode);
uint8_t cp_a_x           (uint8_t *opcode);
uint8_t cp_a_shortoff_x  (uint8_t *opcode);
uint8_t cp_a_longoff_x   (uint8_t *opcode);
uint8_t cp_a_y           (uint8_t *opcode);
uint8_t cp_a_shortoff_y  (uint8_t *opcode);
uint8_t cp_a_longoff_y   (uint8_t *opcode);
uint8_t cp_a_shortoff_sp (uint8_t *opcode);
uint8_t cp_a_shortptr_w  (uint8_t *opcode);
uint8_t cp_a_longptr_w   (uint8_t *opcode);
uint8_t cp_a_shortptr_w_x(uint8_t *opcode);
uint8_t cp_a_longptr_w_x (uint8_t *opcode);
uint8_t cp_a_shortptr_w_y(uint8_t *opcode);


#endif // CP_H

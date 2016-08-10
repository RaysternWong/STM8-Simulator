#ifndef SRL_H
#define SRL_H
#include <stdint.h>

uint8_t srl_a           (uint8_t *opcode);
uint8_t srl_shortmem    (uint8_t *opcode);
uint8_t srl_longmem     (uint8_t *opcode);
uint8_t srl_x           (uint8_t *opcode);
uint8_t srl_shortoff_x  (uint8_t *opcode);
uint8_t srl_longoff_x   (uint8_t *opcode);
uint8_t srl_y           (uint8_t *opcode);
uint8_t srl_shortoff_y  (uint8_t *opcode);
uint8_t srl_longoff_y   (uint8_t *opcode);
uint8_t srl_shortoff_sp (uint8_t *opcode);
uint8_t srl_shortptr_w  (uint8_t *opcode);
uint8_t srl_longptr_w   (uint8_t *opcode);
uint8_t srl_shortptr_w_x(uint8_t *opcode);
uint8_t srl_longptr_w_x (uint8_t *opcode);
uint8_t srl_shortptr_w_y(uint8_t *opcode);

#endif // SRL_H

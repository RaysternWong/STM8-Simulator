#ifndef RRC_H
#define RRC_H
#include <stdint.h>

uint8_t rrc_a           (uint8_t *opcode);
uint8_t rrc_shortmem    (uint8_t *opcode);
uint8_t rrc_longmem     (uint8_t *opcode);
uint8_t rrc_x           (uint8_t *opcode);
uint8_t rrc_shortoff_x  (uint8_t *opcode);
uint8_t rrc_longoff_x   (uint8_t *opcode);
uint8_t rrc_y           (uint8_t *opcode);
uint8_t rrc_shortoff_y  (uint8_t *opcode);
uint8_t rrc_longoff_y   (uint8_t *opcode);
uint8_t rrc_shortoff_sp (uint8_t *opcode);
uint8_t rrc_shortptr_w  (uint8_t *opcode);
uint8_t rrc_longptr_w   (uint8_t *opcode);
uint8_t rrc_shortptr_w_x(uint8_t *opcode);
uint8_t rrc_longptr_w_x (uint8_t *opcode);
uint8_t rrc_shortptr_w_y(uint8_t *opcode);

#endif // RRC_H

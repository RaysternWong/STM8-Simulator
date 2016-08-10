#ifndef SRA_H
#define SRA_H
#include <stdint.h>

uint8_t sra_a           (uint8_t *opcode);
uint8_t sra_shortmem    (uint8_t *opcode);
uint8_t sra_longmem     (uint8_t *opcode);
uint8_t sra_x           (uint8_t *opcode);
uint8_t sra_shortoff_x  (uint8_t *opcode);
uint8_t sra_longoff_x   (uint8_t *opcode);
uint8_t sra_y           (uint8_t *opcode);
uint8_t sra_shortoff_y  (uint8_t *opcode);
uint8_t sra_longoff_y   (uint8_t *opcode);
uint8_t sra_shortoff_sp (uint8_t *opcode);
uint8_t sra_shortptr_w  (uint8_t *opcode);
uint8_t sra_longptr_w   (uint8_t *opcode);
uint8_t sra_shortptr_w_x(uint8_t *opcode);
uint8_t sra_longptr_w_x (uint8_t *opcode);
uint8_t sra_shortptr_w_y(uint8_t *opcode);

#endif // SRA_H

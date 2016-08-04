#ifndef CPW_H
#define CPW_H
#include <stdint.h>

uint8_t cpw_x_word        (uint8_t *opcode);
uint8_t cpw_x_shortmem    (uint8_t *opcode);
uint8_t cpw_x_longmem     (uint8_t *opcode);
uint8_t cpw_x_y           (uint8_t *opcode);
uint8_t cpw_x_shortoff_y  (uint8_t *opcode);
uint8_t cpw_x_longoff_y   (uint8_t *opcode);
uint8_t cpw_x_shortoff_sp (uint8_t *opcode);
uint8_t cpw_x_shortptr_w  (uint8_t *opcode);
uint8_t cpw_x_longptr_w   (uint8_t *opcode);
uint8_t cpw_x_shortptr_w_y(uint8_t *opcode);

uint8_t cpw_y_word        (uint8_t *opcode);
uint8_t cpw_y_shortmem    (uint8_t *opcode);
uint8_t cpw_y_longmem     (uint8_t *opcode);
uint8_t cpw_y_x           (uint8_t *opcode);
uint8_t cpw_y_shortoff_x  (uint8_t *opcode);
uint8_t cpw_y_longoff_x   (uint8_t *opcode);
uint8_t cpw_y_shortptr_w  (uint8_t *opcode);
uint8_t cpw_y_shortptr_w_x(uint8_t *opcode);
uint8_t cpw_y_longptr_w_x(uint8_t *opcode);

#endif // CPW_H

#ifndef ADDW_H
#define ADDW_H
#include <stdint.h>

uint8_t addw_x_ht_word    (uint8_t *opcode);
uint8_t addw_sp_ht_byte   (uint8_t *opcode);
uint8_t addw_x_shortoff_sp(uint8_t *opcode);
uint8_t addw_y_ht_word    (uint8_t *opcode);
uint8_t addw_y_longmem    (uint8_t *opcode);
uint8_t addw_y_shortoff_sp(uint8_t *opcode);
uint8_t addw_sp_ht_byte   (uint8_t *opcode);

#endif // ADDW_H

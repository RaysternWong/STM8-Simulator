#ifndef LDF_H
#define LDF_H
#include <stdint.h>

uint8_t ldf_a_extmem       (uint8_t *opcode);
uint8_t ldf_a_extoff_x     (uint8_t *opcode);
uint8_t ldf_a_extoff_y     (uint8_t *opcode);
uint8_t ldf_a_longptr_e_x  (uint8_t *opcode);
uint8_t ldf_a_longptr_e_y  (uint8_t *opcode);
uint8_t ldf_a_longptr_e    (uint8_t *opcode);

uint8_t ldf_a_to_extmem       (uint8_t *opcode);
uint8_t ldf_a_to_extoff_x     (uint8_t *opcode);
uint8_t ldf_a_to_extoff_y     (uint8_t *opcode);
uint8_t ldf_a_to_longptr_e_x  (uint8_t *opcode);
uint8_t ldf_a_to_longptr_e_y  (uint8_t *opcode);
uint8_t ldf_a_to_longptr_e    (uint8_t *opcode);

#endif // LDF_H

#ifndef SUBW_H
#define SUBW_H
#include <stdint.h>

uint8_t subw_x_word       (uint8_t *opcode);
uint8_t subw_x_longmem    (uint8_t *opcode);
uint8_t subw_x_shortoff_sp(uint8_t *opcode);
uint8_t subw_y_word       (uint8_t *opcode);
uint8_t subw_y_longmem    (uint8_t *opcode);
uint8_t subw_y_shortoff_sp(uint8_t *opcode);


#endif // SUBW_H

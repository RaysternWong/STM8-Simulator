#ifndef RRCW_H
#define RRCW_H
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t rrcw_x(uint8_t *opcode);
uint8_t rrcw_y(uint8_t *opcode);

#endif // RRCW_H

#ifndef MOV_H
#define MOV_H
#include <stdint.h>

uint8_t mov_longmem_byte        (uint8_t *opcode);
uint8_t mov_shortmem_shortmem   (uint8_t *opcode);
uint8_t mov_longmem_longmem     (uint8_t *opcode);

#endif // MOV_H

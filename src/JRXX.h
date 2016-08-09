#ifndef JRXX_H
#define JRXX_H
#include <stdint.h>

uint8_t jrc  (uint8_t *opcode);
uint8_t jreq (uint8_t *opcode);
uint8_t jrf  (uint8_t *opcode);
uint8_t jrh  (uint8_t *opcode);
uint8_t jrih (uint8_t *opcode);
uint8_t jril (uint8_t *opcode);
uint8_t jrm  (uint8_t *opcode);
uint8_t jrmi (uint8_t *opcode);
uint8_t jrnc (uint8_t *opcode);
uint8_t jrne (uint8_t *opcode);
uint8_t jrnh (uint8_t *opcode);
uint8_t jrnm (uint8_t *opcode);
uint8_t jrnv (uint8_t *opcode);
uint8_t jrpl (uint8_t *opcode);
uint8_t jrsge(uint8_t *opcode);
uint8_t jrsgt(uint8_t *opcode);
uint8_t jrsle(uint8_t *opcode);
uint8_t jrslt(uint8_t *opcode);
uint8_t jrt  (uint8_t *opcode);
uint8_t jruge(uint8_t *opcode);
uint8_t jrugt(uint8_t *opcode);
uint8_t jrule(uint8_t *opcode);
uint8_t jrult(uint8_t *opcode);
uint8_t jrv  (uint8_t *opcode);


#endif // JRXX_H

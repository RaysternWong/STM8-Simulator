#ifndef InstructionTable_H
#define InstructionTable_H
#include <stdint.h>

typedef uint8_t (*Instruction)(uint8_t *opcode);

Instruction firstOpcode[256];
Instruction opcode72[256];


#endif // InstructionTable_H

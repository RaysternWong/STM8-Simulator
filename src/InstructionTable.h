#ifndef InstructionTable_H
#define InstructionTable_H
#include <stdint.h>

typedef uint8_t (*Instruction)(uint8_t *opcode);

Instruction firstOpcode[256];
Instruction opcode72[256];
Instruction opcode90[256];
Instruction opcode91[256];
Instruction opcode92[256];

uint8_t executeInstructionThroughOpcode(uint8_t *opcode);


#endif // InstructionTable_H

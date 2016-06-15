#include "InstructionTable.h"
#include <stdio.h>
#include <stdint.h>
#include "ADDW.h"




Instruction firstOpcode[256] = {
  [0x1c] = addw_x_ht_word,
  [0x5b] = addw_sp_ht_byte,
};


Instruction opcode72[256] = {
  
};

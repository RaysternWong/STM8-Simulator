#include "InstructionTable.h"
#include <stdio.h>
#include <stdint.h>
#include "ADDW.h"


Instruction firstOpcode[256] = {
  
  // ADDW
  [0x1c] = addw_x_ht_word,
  [0x5b] = addw_sp_ht_byte,
};


Instruction opcode72[256] = {
  
  // ADDW
  [0xBB] = addw_x_ht_word,
  [0xFB] = addw_x_ht_word,
  [0xA9] = addw_x_ht_word,
  [0xB9] = addw_x_ht_word,
  [0xF9] = addw_x_ht_word,
};


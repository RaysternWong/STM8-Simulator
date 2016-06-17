#include "InstructionTable.h"
#include <stdio.h>
#include <stdint.h>
#include "ADDW.h"
#include "ADD.h"
#include "ADC.h"
#include "ErrorCode.h"


Instruction firstOpcode[256] = {
  
  // ADD
  [0xAB] = add_a_ht_byte,
  [0xBB] = add_a_shortmem,
  [0xCB] = add_a_longmem,
  [0xFB] = add_a_x,
  [0xEB] = add_a_shortoff_x,
  [0xDB] = add_a_longoff_x,
  [0x1B] = add_a_shortoff_sp,
  
  // ADDW
  [0x1c] = addw_x_ht_word,
  [0x5b] = addw_sp_ht_byte,
};


Instruction opcode72[256] = {
  
  // ADD
  [0xCB] = add_a_longptr_w,
  [0xDB] = add_a_longptr_w_x,
  
  
  // ADDW
  [0xBB] = addw_x_longmem,
  [0xFB] = addw_x_shortoff_sp,
  [0xA9] = addw_y_ht_word,
  [0xB9] = addw_y_longmem,
  [0xF9] = addw_y_shortoff_sp,
};

Instruction opcode90[256] = {
  // ADD
  [0xFB] = add_a_y,
  [0xEB] = add_a_shortoff_y,
  [0xDB] = add_a_longoff_y,

};

Instruction opcode91[256] = {
  // ADD
  [0xDB] = add_a_shortptr_w_y,

};

Instruction opcode92[256] = {
  // ADD
  [0xCB] = add_a_shortptr_w,
  [0xDB] = add_a_shortptr_w_x,
};

uint8_t getInstructionLength(uint8_t *opcode)
{
  uint8_t length = 0;
  
  switch(*opcode)
  {
    case 0x72 : *opcode++;
                length = opcode72[*opcode](opcode); 
                break;
                
    case 0x90 : *opcode++;
                length = opcode90[*opcode](opcode);  
                break;
                
    case 0x91 : *opcode++;
                length = opcode91[*opcode](opcode); 
                break;
                
    case 0x92 : *opcode++;
                length = opcode92[*opcode](opcode); 
                break;
    
    default   : length = firstOpcode[*opcode](opcode); 
                //Throw(ERR_INSTRUCTION_NOT_IN_TABLE);
                break;
  }
  return length;
}
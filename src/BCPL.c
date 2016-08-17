#include "BCPL.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

/**  Example : byte = 1111 11111
                                 
               if complement bit is is bit0, magicValue = 0x1;
               
               if bit0 is 0, then byte | 0x01
               if bit0 is 1, then byte & ~0x01 ( ~0x01 = 0xF0)
                                 

*/
#define BCPL(bitNum,magicValue)   MEM_WRITE_BYTE(longmem, (bitNum) == 0 ? (byte|magicValue) : (byte & ~magicValue) );

/**
*          Binary       Hex
*       0000 0001         1     bit 0
*       0000 0010         2
*       0000 0100         4
*       0000 1000         8
*       0001 0000        10
*       0010 0000        20
*       0100 0000        40
*       1000 0000        80     bit 7

          Binary        Hex
        1111  1110    0xFE
        1111  1101    0xFD    
        1111  1011    0xFB
        1111  0111    0xF7
        1110  1111    0xEF
        1101  1111    0xDF
        1011  1111    0xBF
        0111  1111    0x7F
        
        where 0xFE = ~0x01 , 0xFD = ~0x02 ..............
*/

uint8_t bcpl_longmem_pos_0(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_0(byte), 0x1);
  return 4;
}

uint8_t bcpl_longmem_pos_1(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_1(byte), 0x2);
  return 4;
}

uint8_t bcpl_longmem_pos_2(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_2(byte), 0x4);
  return 4;
}

uint8_t bcpl_longmem_pos_3(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_3(byte), 0x8);
  return 4;
}

uint8_t bcpl_longmem_pos_4(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_4(byte), 0x10);
  return 4;
}

uint8_t bcpl_longmem_pos_5(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_5(byte), 0x20);
  return 4;
}
uint8_t bcpl_longmem_pos_6(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_6(byte), 0x40);
  return 4;
}

uint8_t bcpl_longmem_pos_7(uint8_t *opcode){
  uint16_t longmem = GET_LONG_MEM(opcode); 
  uint8_t  byte = MEM_READ_BYTE(longmem);
  
  BCPL(GET_BIT_7(byte), 0x80);
  return 4;
}
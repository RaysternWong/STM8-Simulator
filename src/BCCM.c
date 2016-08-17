#include "BCCM.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define BCCM(num) uint16_t longmem = GET_LONG_MEM(opcode); MEM_WRITE_BYTE(longmem, MEM_READ_BYTE(longmem) | num );


/**
     Binary        Hex
    1111  1110    0xFE
    1111  1101    0xFD    
    1111  1011    0xFB
    1111  0111    0xF7
    1110  1111    0xEF
    1101  1111    0xDF
    1011  1111    0xBF
    0111  1111    0x7F
*/

uint8_t bccm_longmem_pos_0(uint8_t *opcode){
  BCCM(C);
  return 4;
}

uint8_t bccm_longmem_pos_1(uint8_t *opcode){
  BCCM(C<<1);
  return 4;
}

uint8_t bccm_longmem_pos_2(uint8_t *opcode){
  BCCM(C<<2);
  return 4;
}

uint8_t bccm_longmem_pos_3(uint8_t *opcode){
  BCCM(C<<3);
  return 4;
}

uint8_t bccm_longmem_pos_4(uint8_t *opcode){
  BCCM(C<<4);
  return 4;
}

uint8_t bccm_longmem_pos_5(uint8_t *opcode){
  BCCM(C<<5);
  return 4;
}
uint8_t bccm_longmem_pos_6(uint8_t *opcode){
  BCCM(C<<6);
  return 4;
}

uint8_t bccm_longmem_pos_7(uint8_t *opcode){
  BCCM(C<<7);
  return 4;
}
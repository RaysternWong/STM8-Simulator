#include "ADC.h"
#include <stdio.h>
#include <stdint.h>

/**
*  Please refer the folowing instruction in the page 77 of programming manual
*
*   'a'  means accumulator
*   'ht' means hast tag , #
*/

uint8_t adc_a_ht_byte(uint8_t *opcode){
  opcode++;
  return 2;
}

uint8_t adc_a_shortmem(uint8_t *opcode){
  opcode++;
  return 2;
}

uint8_t adc_a_longmem(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t adc_a_x(uint8_t *opcode){
  opcode++;
  return 1;
}

uint8_t adc_a_shortoff_x(uint8_t *opcode){
  opcode++;
  return 2;
}

uint8_t adc_a_longoff_x(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t adc_a_y(uint8_t *opcode){
  opcode++;
  return 2;
}

uint8_t adc_a_shortoff_y(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t adc_a_longoff_y(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t adc_a_shortoff_sp(uint8_t *opcode){
  opcode++;
  return 2;
}

uint8_t adc_a_shortptr_w(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t adc_a_longptr_w(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t adc_a_shortptr_w_x(uint8_t *opcode){
  opcode++;
  return 3;
}

uint8_t adc_a_longptr_w_x(uint8_t *opcode){
  opcode++;
  return 4;
}

uint8_t adc_a_shortptr_w_y(uint8_t *opcode){
  opcode++;
  return 3;
}
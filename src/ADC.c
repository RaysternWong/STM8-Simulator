#include "ADC.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t adc_a_byte(uint8_t *opcode){
  mcu_adc( GET_BYTE(opcode) );
  return 2;
}

uint8_t adc_a_shortmem(uint8_t *opcode){
  mcu_adc(getShortMemSrc(opcode));
  return 2;
}

uint8_t adc_a_longmem(uint8_t *opcode){
  mcu_adc( getLongMemSrc(opcode) );
  return 3;
}


uint8_t adc_a_x(uint8_t *opcode){

  mcu_adc( X_SRC);
  return 1;
}

uint8_t adc_a_shortoff_x(uint8_t *opcode){
  mcu_adc( getShortOffXSrc(opcode) );
  return 2;
}

uint8_t adc_a_longoff_x(uint8_t *opcode){
  mcu_adc( getLongOffXSrc(opcode) );
  return 3;
}


uint8_t adc_a_y(uint8_t *opcode){
  mcu_adc(  Y_SRC );
  return 2;
}

uint8_t adc_a_shortoff_y(uint8_t *opcode){
  mcu_adc( getShortOffYSrc(opcode) );
  return 3;
}

uint8_t adc_a_longoff_y(uint8_t *opcode){
  mcu_adc( getLongOffYSrc(opcode) );
  return 4;
}

uint8_t adc_a_shortoff_sp(uint8_t *opcode){
  mcu_adc( getShortOffSPSrc(opcode) );
  return 2;
}

uint8_t adc_a_shortptr_w(uint8_t *opcode){
  mcu_adc( getShortPtrWSrc(opcode) );
  return 3;
}

uint8_t adc_a_longptr_w(uint8_t *opcode){
  mcu_adc( getLongPtrWSrc(opcode) );
  return 4;
}

uint8_t adc_a_shortptr_w_x(uint8_t *opcode){
  mcu_adc( getShortPtrWXSrc(opcode) );
  return 3;
}

uint8_t adc_a_longptr_w_x(uint8_t *opcode){
  mcu_adc( getLongPtrWXSrc(opcode) );
  return 4;
}

uint8_t adc_a_shortptr_w_y(uint8_t *opcode){
  mcu_adc( getShortPtrWYSrc(opcode) ); 
  return 3;
}





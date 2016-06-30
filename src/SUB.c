#include "SUB.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"


/**
*           Binary       Hex
*       0000 0001         1     bit 0
*       0000 0010         2
*       0000 0100         4
*       0000 1000         8
*       0001 0000        10
*       0010 0000        20
*       0100 0000        40
*       1000 0000        80     bit 7
*
*                       100    bit 8
*                       200
*                       400
*                       800
*                      1000
*                      2000
*                      4000
*                      8000    bit 15

*/

// Memory
#define M0  (value & 0X01)      
#define M1  ( (value & 0X02) >> 1 )
#define M2  ( (value & 0X04) >> 2 )
#define M3  ( (value & 0X08) >> 3 )
#define M4  ( (value & 0X10) >> 4 )
#define M5  ( (value & 0X20) >> 5 )
#define M6  ( (value & 0X40) >> 6 )
#define M7  ( (value & 0X80) >> 7 )


// Accumulator (or others register like index X,Y,SP)
#define A0  (a & 0X01) 
#define A1  ((a & 0X02) >> 1)
#define A2  ((a & 0X04) >> 2)
#define A3  ((a & 0X08) >> 3)
#define A4  ((a & 0X10) >> 4)
#define A5  ((a & 0X20) >> 5)
#define A6  ((a & 0X40) >> 6)
#define A7  ((a & 0X80) >> 7)

// Result
#define R0  (result & 0X01)
#define R1  ((result & 0X02) >> 1)
#define R2  ((result & 0X04) >> 2)
#define R3  ((result & 0X08) >> 3)
#define R4  ((result & 0X10) >> 4)
#define R5  ((result & 0X20) >> 5)
#define R6  ((result & 0X40) >> 6)
#define R7  ((result & 0X80) >> 7)

// Bitwise result
#define _A0  (A0 == 0 ? 1 : 0)
#define _A1  (A1 == 0 ? 1 : 0)
#define _A2  (A2 == 0 ? 1 : 0)
#define _A3  (A3 == 0 ? 1 : 0)
#define _A4  (A4 == 0 ? 1 : 0)
#define _A5  (A5 == 0 ? 1 : 0)
#define _A6  (A6 == 0 ? 1 : 0)
#define _A7  (A7 == 0 ? 1 : 0)

#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)

#define V   ((cpu->ccr).bits.v)   //overFlow
#define L1  ((cpu->ccr).bits.l1)  //interrupt mask level 1
#define H   ((cpu->ccr).bits.h)   //half cary
#define L0  ((cpu->ccr).bits.l0)  //interrupt mask level 0
#define N   ((cpu->ccr).bits.n)   //negative
#define Z   ((cpu->ccr).bits.z)   //zero
#define C   ((cpu->ccr).bits.c)   //carry

void mcu_sub(uint8_t value)
{
  uint8_t a       = cpu->a;
  uint8_t result  = a - value;
  cpu->a          = result;
  
  N = R7;
  Z = (result == 0 ? 1 : 0);

  C = _A7 & M7 | _A7 & R7 | A7 & M7 & A7;
  V = (A7 & M7 | A7 & R7 | A7 & M7 & R7) ^ (A6 & M6 | A6 & R6 | A6 & M6 & R6) ;
}

uint8_t sub_a_byte(uint8_t *opcode){
  opcode++;
  mcu_sub(*opcode);
  return 2;
}

uint8_t sub_a_shortmem(uint8_t *opcode){
  opcode++;
  uint8_t value =  getValueFromAddress(*opcode);
  mcu_sub(value);
  return 2;
}

uint8_t sub_a_longmem(uint8_t *opcode){
  
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fulladdr = combineMostLeastByte( msb , lsb);

  uint8_t  value    = getValueFromAddress(fulladdr);
  mcu_sub(value);
  return 3;
}

uint8_t sub_a_x(uint8_t *opcode){

  uint16_t x     = combineMostLeastByte( XH , XL);
  uint8_t  value = getValueFromAddress(x);
  
  mcu_sub(value);
  return 1;
}

uint8_t sub_a_shortoff_x(uint8_t *opcode){
  opcode++;

  uint16_t x = combineMostLeastByte( XH , XL);
           x += *opcode;
  uint8_t  value =  getValueFromAddress(x);
  mcu_sub(value);
  return 2;
}

uint8_t sub_a_longoff_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fulladdr = combineMostLeastByte( msb , lsb);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fulladdr;

  uint8_t  value = getValueFromAddress(x);
  mcu_sub(value);
  return 3;
}


uint8_t sub_a_y(uint8_t *opcode){
  uint16_t y     = combineMostLeastByte( YH , YL);
  uint8_t  value = getValueFromAddress(y);
  
  mcu_sub(value);
  return 2;
}

uint8_t sub_a_shortoff_y(uint8_t *opcode){
  opcode++;

  uint16_t y = combineMostLeastByte( YH , YL);
           y += *opcode;
  uint8_t  value =  getValueFromAddress(y);
  mcu_sub(value);
  return 3;
}

uint8_t sub_a_longoff_y(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fulladdr = combineMostLeastByte( msb , lsb);
  uint16_t y        = combineMostLeastByte( YH , YL);
           y       += fulladdr;

  uint8_t  value = getValueFromAddress(y);
  mcu_sub(value);
  return 4;
}

uint8_t sub_a_shortoff_sp(uint8_t *opcode){
  opcode++;

  uint16_t sp = combineMostLeastByte( SPH , SPL);
           sp += *opcode;
  uint8_t  value =  getValueFromAddress(sp);
  mcu_sub(value);
  return 2;
}

uint8_t sub_a_shortptr_w(uint8_t *opcode){
  
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fulladdr = combineMostLeastByte( value1 , value2);
  uint8_t  value    = getValueFromAddress(fulladdr);
  mcu_sub(value);

  return 3;
}

uint8_t sub_a_longptr_w(uint8_t *opcode){
  
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fulladdr1 = combineMostLeastByte( msb , lsb);
  
  uint8_t  value1 =  getValueFromAddress( fulladdr1);
  uint8_t  value2 =  getValueFromAddress( fulladdr1 + 1 );
  
  uint16_t fulladdr = combineMostLeastByte( value1 , value2);
  uint8_t  value    = getValueFromAddress(fulladdr);
  mcu_sub(value);

  return 4;
}

uint8_t sub_a_shortptr_w_x(uint8_t *opcode){
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fulladdr = combineMostLeastByte( value1 , value2);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fulladdr;
           
  uint8_t  value    = getValueFromAddress(x);
  mcu_sub(value); 
  return 3;
}

uint8_t sub_a_longptr_w_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fulladdr1 = combineMostLeastByte( msb , lsb);
  
  uint8_t  value1 =  getValueFromAddress( fulladdr1);
  uint8_t  value2 =  getValueFromAddress( fulladdr1 + 1 );
  
  uint16_t fulladdr = combineMostLeastByte( value1 , value2);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fulladdr;
          
  uint8_t  value    = getValueFromAddress(x);
  mcu_sub(value); 
  return 4;
}

uint8_t sub_a_shortptr_w_y(uint8_t *opcode){
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fulladdr = combineMostLeastByte( value1 , value2);
  uint16_t y        = combineMostLeastByte( YH , YL);
           y       += fulladdr;
           
  uint8_t  value    = getValueFromAddress(y);
  mcu_sub(value); 
  return 3;
}
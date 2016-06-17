#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"

/**
*           Binary       Hex
*       0000 0001         1
*       0000 0010         2
*       0000 0100         4
*       0000 1000         8
*       0001 0000        10
*       0010 0000        20
*       0100 0000        40
*       1000 0000        80
*
*/


#define R0  (result & 0X01)
#define R1  (result & 0X02) >> 1
#define R2  (result & 0X04) >> 2
#define R3  (result & 0X08) >> 3
#define R4  (result & 0X10) >> 4
#define R5  (result & 0X20) >> 5
#define R6  (result & 0X40) >> 6
#define R7  (result & 0X80) >> 7

#define M0  (value & 0X01)
#define M1  (value & 0X02) >> 1
#define M2  (value & 0X04) >> 2
#define M3  (value & 0X08) >> 3
#define M4  (value & 0X10) >> 4
#define M5  (value & 0X20) >> 5
#define M6  (value & 0X40) >> 6
#define M7  (value & 0X80) >> 7

#define A0  (A & 0X01)
#define A1  (A & 0X02) >> 1
#define A2  (A & 0X04) >> 2
#define A3  (A & 0X08) >> 3
#define A4  (A & 0X10) >> 4
#define A5  (A & 0X20) >> 5
#define A6  (A & 0X40) >> 6
#define A7  (A & 0X80) >> 7

#define FLAG (cpu->ccR)


void mcu_add(CPU *cpu, uint8_t value)
{
   // Accumulator
  
  
  
  uint8_t A = cpu->accA ;
  uint8_t result = A + value;
  

  if(result>0)
    FLAG.Z = 0;
  else 
    FLAG.Z = 1;

  
  cpu->accA = result;
}
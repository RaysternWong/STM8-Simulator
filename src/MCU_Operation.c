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

void mcu_add(CPU *cpu, uint8_t value)
{
  uint8_t A = cpu->accA ;
  uint8_t result = A + value;
  
  cpu->accA = result;
}
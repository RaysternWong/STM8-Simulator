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

// Memory
#define M0  (value & 0X01)
#define M1  (value & 0X02) >> 1
#define M2  (value & 0X04) >> 2
#define M3  (value & 0X08) >> 3
#define M4  (value & 0X10) >> 4
#define M5  (value & 0X20) >> 5
#define M6  (value & 0X40) >> 6
#define M7  (value & 0X80) >> 7

// Accumulator
#define A0  (a & 0X01)
#define A1  (a & 0X02) >> 1
#define A2  (a & 0X04) >> 2
#define A3  (a & 0X08) >> 3
#define A4  (a & 0X10) >> 4
#define A5  (a & 0X20) >> 5
#define A6  (a & 0X40) >> 6
#define A7  (a & 0X80) >> 7

// Result
#define R0  (result & 0X01)
#define R1  (result & 0X02) >> 1
#define R2  (result & 0X04) >> 2
#define R3  (result & 0X08) >> 3
#define R4  (result & 0X10) >> 4
#define R5  (result & 0X20) >> 5
#define R6  (result & 0X40) >> 6
#define R7  (result & 0X80) >> 7

// Bitwised result
#define _R0  (R0 == 0 ? 1 : 0)
#define _R1  (R1 == 0 ? 1 : 0)
#define _R2  (R2 == 0 ? 1 : 0)
#define _R3  (R3 == 0 ? 1 : 0)
#define _R4  (R4 == 0 ? 1 : 0)
#define _R5  (R5 == 0 ? 1 : 0)
#define _R6  (R6 == 0 ? 1 : 0)
#define _R7  (R7 == 0 ? 1 : 0)

void mcu_add(uint8_t value)
{
  uint8_t a       = cpu.accA;
  uint8_t result  = a + value;
  cpu.accA        = result;

  cpu.ccR.V = ( A7 & M7 | M7 & _R7 | _R7 & A7 ) ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
  cpu.ccR.H = A3 & M3 | M3 & _R3 | _R3 & A3;
  cpu.ccR.N = R7;
  cpu.ccR.Z = (result == 0 ? 1 : 0);
  cpu.ccR.C = A7 & M7 | M7 & _R7 | _R7 & A7;
}

void mcu_adc(uint8_t value)
{
  uint8_t a       = cpu.accA;
  uint8_t result  = a + value + cpu.ccR.C;
  cpu.accA += result;

  cpu.ccR.V = ( A7 & M7 | M7 & _R7 | _R7 & A7 ) ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
  cpu.ccR.H = A3 & M3 | M3 & _R3 | _R3 & A3;
  cpu.ccR.N = R7;
  cpu.ccR.Z = (result == 0 ? 1 : 0);
  cpu.ccR.C = A7 & M7 | M7 & _R7 | _R7 & A7;
}

void mcu_addw(uint16_t *reg, uint16_t value){
  uint16_t dst    = *reg;
  uint16_t result = dst + value;
  *reg = result;
}
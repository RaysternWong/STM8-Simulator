#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

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

#define M8  ( (value & 0X100) >> 8 )
#define M9  ( (value & 0X200) >> 9 )
#define M10 ( (value & 0X400) >> 10)
#define M11 ( (value & 0X800) >> 11)
#define M12 ( (value & 0X1000) >> 12)
#define M13 ( (value & 0X2000) >> 13)
#define M14 ( (value & 0X4000) >> 14)
#define M15 ( (value & 0X8000) >> 15)


// Accumulator (or others register like index X,Y,SP)
#define A0  (a & 0X01) 
#define A1  ((a & 0X02) >> 1)
#define A2  ((a & 0X04) >> 2)
#define A3  ((a & 0X08) >> 3)
#define A4  ((a & 0X10) >> 4)
#define A5  ((a & 0X20) >> 5)
#define A6  ((a & 0X40) >> 6)
#define A7  ((a & 0X80) >> 7)

#define A8  ((a & 0X100) >> 8)
#define A9  ((a & 0X200) >> 9)
#define A10 ((a & 0X400) >> 10)
#define A11 ((a & 0X800) >> 11)
#define A12 ((a & 0X1000) >> 12)
#define A13 ((a & 0X2000) >> 13)
#define A14 ((a & 0X4000) >> 14)
#define A15 ((a & 0X8000) >> 15)

// Result
#define R0  (result & 0X01)
#define R1  ((result & 0X02) >> 1)
#define R2  ((result & 0X04) >> 2)
#define R3  ((result & 0X08) >> 3)
#define R4  ((result & 0X10) >> 4)
#define R5  ((result & 0X20) >> 5)
#define R6  ((result & 0X40) >> 6)
#define R7  ((result & 0X80) >> 7)

#define R8  ((result & 0X100) >> 8)
#define R9  ((result & 0X200) >> 9)
#define R10 ((result & 0X400) >> 10)
#define R11 ((result & 0X800) >> 11)
#define R12 ((result & 0X1000) >> 12)
#define R13 ((result & 0X2000) >> 13)
#define R14 ((result & 0X4000) >> 14)
#define R15 ((result & 0X8000) >> 15)

// Bitwise result
#define _R0  (R0 == 0 ? 1 : 0)
#define _R1  (R1 == 0 ? 1 : 0)
#define _R2  (R2 == 0 ? 1 : 0)
#define _R3  (R3 == 0 ? 1 : 0)
#define _R4  (R4 == 0 ? 1 : 0)
#define _R5  (R5 == 0 ? 1 : 0)
#define _R6  (R6 == 0 ? 1 : 0)
#define _R7  (R7 == 0 ? 1 : 0)

#define _R8  (R8 == 0 ? 1 : 0)
#define _R9  (R9 == 0 ? 1 : 0)
#define _R10 (R10 == 0 ? 1 : 0)
#define _R11 (R11 == 0 ? 1 : 0)
#define _R12 (R12 == 0 ? 1 : 0)
#define _R13 (R13 == 0 ? 1 : 0)
#define _R14 (R14 == 0 ? 1 : 0)
#define _R15 (R15 == 0 ? 1 : 0)

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


uint16_t getBigEndianWord(uint8_t mostByte, uint8_t leastByte)
{
  return ( (mostByte<<8) + leastByte);
}

void setBigEndianWord(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte)
{
  *mostByte  = fullByte >> 8;
  *leastByte = fullByte & 0x00FF;
}

void setBigEndianMSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte)
{
  *mostByte  = fullByte >> 8;
}

void setBigEndianLSB(uint8_t *mostByte, uint8_t *leastByte, uint16_t fullByte)
{
  *leastByte = fullByte & 0x00FF;
}

void mcu_add(uint8_t value)
{
  uint8_t a       = cpu->a;
  uint8_t result  = a + value;
  cpu->a          = result;
  
  N = R7;
  Z = (result == 0 ? 1 : 0);
  H = A3 & M3 | M3 & _R3 | _R3 & A3;
  C = A7 & M7 | M7 & _R7 | _R7 & A7;
  V = C ^ ( A6 & M6 | M6 & _R6 | _R6 & A6 );
}

void mcu_addw(uint8_t *mostByte, uint8_t *leastByte, uint16_t value)
{
  uint16_t a  = getBigEndianWord(*mostByte, *leastByte);
  uint16_t result = a + value;
  setBigEndianWord( mostByte, leastByte, result);

  N = R15;
  Z = (result == 0 ? 1 : 0);
  H = A7 & M7 | M7 & _R7 | _R7 & A7;
  C = A15 & M15 | M15 & _R15 | _R15 & A15;
  V = C ^ ( A14 & M14 | M14 & _R14 | _R14 & A14 );
}


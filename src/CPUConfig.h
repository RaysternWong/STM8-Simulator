#ifndef CPUConfig_H
#define CPUConfig_H
#include <stdint.h>
#include "Memory.h"
// struct Flag{ //Condition Flag
  // int V;  // OverFlow
  // int l1; // Interrupt mask level 1
  // int H;  // Half carry bit
  // int l0; // Interrupt mask level 0
  // int N;  // Negative
  // int Z;  // Zero
  // int C;  // Carry
// };



typedef struct CPU_t CPU_t;

typedef struct{
  uint8_t V :1;
  uint8_t l1:1;
  uint8_t H :1;
  uint8_t l0:1;
  uint8_t N :1;
  uint8_t Z :1;
  uint8_t C :1;
}Bits;

typedef union{
  Bits    bits;
  uint8_t full;
}Flag;

struct CPU_t{
  uint8_t   a;     //Accumulator
  
  uint8_t   pce;    //Program counter
  uint8_t   pch;     
  uint8_t   pcl;   
  
  uint8_t   xh;    
  uint8_t   xl; 
  
  uint8_t   yh;  
  uint8_t   yl;   
  
  uint16_t  sph; 
  uint16_t  spl; 
   
  Flag      ccr ;     //Condition Code Register
};

extern CPU_t *cpu;


#endif // CPUConfig_H

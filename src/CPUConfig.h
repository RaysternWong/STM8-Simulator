#ifndef CPUConfig_H
#define CPUConfig_H
#include <stdint.h>


typedef struct Flag Flag;
typedef struct CPU_t CPU_t;

struct Flag{ //Condition Flag
  int V;  // OverFlow
  int l1; // Interrupt mask level 1
  int H;  // Half carry bit
  int l0; // Interrupt mask level 0
  int N;  // Negative
  int Z;  // Zero
  int C;  // Carry
};



struct CPU_t{
  uint8_t   accA;     //Accumulator
  uint16_t  index_X;  //Index registers X 
  uint16_t  index_Y;  //Index registers Y
  uint16_t  sp;       //Stack pointer
  uint32_t  PC;       //Program counter
  Flag      ccR ; //Condition Code Register
};

extern CPU_t cpu;

#endif // CPUConfig_H

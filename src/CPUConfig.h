#ifndef CPUConfig_H
#define CPUConfig_H
#include <stdint.h>


typedef struct Flag Flag;

struct Flag{ //Condition Flag
  int V;  // OverFlow
  int l1; // Interrupt mask level 1
  int H;  // Half carry bit
  int l0; // Interrupt mask level 0
  int N;  // Negative
  int Z;  // Zero
  int C;  // Carry
};



typedef struct CPU_t{
  uint8_t accA; //Accumulator
  Flag    ccR ; //Condition Code Register
  
}CPU;



#endif // CPUConfig_H

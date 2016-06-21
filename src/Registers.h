#ifndef Registers_H
#define Registers_H

typedef struct ConditionCodeRegister ConditionCodeRegister;

struct ConditionCodeRegister{ //Condition Flag
  int V;  // OverFlow
  int l1; // Interrupt mask level 1
  int H;  // Half carry bit
  int l0; // Interrupt mask level 0
  int N;  // Negative
  int Z;  // Zero
  int C;  // Carry
};

#endif // Registers_H

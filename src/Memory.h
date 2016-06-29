#ifndef Memory_H
#define Memory_H
#include "CPUConfig.h"
#include <stdint.h>

typedef uint8_t Memory;

void writeCPU(void);
void readCPU(void);

//void writeCPU(CPU_t *cpu);

extern Memory cp_addr[0xFF];



#endif // Memory_H


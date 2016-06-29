#include "Memory.h"
#include <stdint.h>
#include <malloc.h>
#include "CPUConfig.h"

/**
*  Memory register map 
*
*  from 0x00 0000 to 0x02 7FFF
*
*  which is 0 to 163839
*/

//Memory *cpu_addr = malloc( sizeof(Memory) );

Memory cp_addr[0xFF];

//uint8_t cpu_addr[0xFF];




//uint8_t *cpu_addr = malloc( sizeof(uint8_t) );

//cpu_addr[0xFF];

void readCPU(void)
{
  cpu->a = cp_addr[0x00];
  
  //(cpu->a) = *( (uint8_t*)(cp_addr[0x00]) ) ;
}


void writeCPU(void)
{
  cp_addr[0x00] = cpu->a;
  
  // cpu_addr[0x00] = (cpu->a);
  // cpu_addr[0x01] = cpu->pce;
  // cpu_addr[0x02] = cpu->pch;
  // cpu_addr[0x03] = cpu->pcl;
  // cpu_addr[0x04] = cpu->xh;
  // cpu_addr[0x05] = cpu->xl;
  // cpu_addr[0x06] = cpu->yh;
  // cpu_addr[0x07] = cpu->yl;
  // cpu_addr[0x08] = cpu->sph;
  // cpu_addr[0x09] = cpu->spl;
  // cpu_addr[0x0A] = cpu->ccr;
}
#include "CPUConfig.h"
#include <stdint.h>
#include <malloc.h>
#include "Memory.h"

//CPU_t *cpu = malloc( sizeof(CPU_t) );


CPU_t *cpu =&mcu_memory[0x007F00];




// cpu->a    = mcu_memory[0x007F00];
// cpu->pce  = mcu_memory[0x007F01];
// cpu->pch  = mcu_memory[0x007F02];
// cpu->pcl  = mcu_memory[0x007F03];
// cpu->xh   = mcu_memory[0x007F04];
// cpu->xl   = mcu_memory[0x007F05];
// cpu->yh   = mcu_memory[0x007F06];
// cpu->yl   = mcu_memory[0x007F07];
// cpu->sph  = mcu_memory[0x007F08];
// cpu->spl  = mcu_memory[0x007F09];
// cpu->ccr  = mcu_memory[0x007F09];

void clearConditionCodeRegister(Flag *ccR)
{
  //ccR->full = 0;
  //(ccR->bits).V;
  //(ccR->bits).V  = 0;
  // (ccR->bits).l1 = 0;
  // (ccR->bits).H  = 0;
  // (ccR->bits).l0 = 0;
  // (ccR->bits).N  = 0;
  // (ccR->bits).Z  = 0;
  // (ccR->bits).C  = 0;
}







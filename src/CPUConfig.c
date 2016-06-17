#include "CPUConfig.h"
#include <stdint.h>

void clearConditionCodeRegister(Flag *ccR)
{
  ccR->V  = 0;
  ccR->l1 = 0;
  ccR->H  = 0;
  ccR->l0 = 0;
  ccR->N  = 0;
  ccR->Z  = 0;
  ccR->C  = 0;
}



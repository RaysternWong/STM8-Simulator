#include "TRAP.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t trap(uint8_t *opcode){
  *pcToLoad += 1; 

  mcu_push(GET_LEAST_BYTE(*pcToLoad));
  mcu_push(GET_MID_BYTE(*pcToLoad));
  mcu_push(GET_MOST_BYTE(*pcToLoad));
  mcu_push(YL);
  mcu_push(YH);
  mcu_push(XL);
  mcu_push(XH);
  mcu_push(A);
  mcu_push(CC);
 
  I0 = 1;
  I1 = 1;
  return 1;
}
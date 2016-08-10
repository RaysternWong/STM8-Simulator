#include "TRAP.h"
#include "MCU_Operation.h"
#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

uint8_t trap(uint8_t *opcode){
  uint32_t newPC = PC + 1;
  SET_PC(newPC);
  
  mcu_push(PCL);
  mcu_push(PCH);
  mcu_push(PCE);
  mcu_push(YL);
  mcu_push(YH);
  mcu_push(XL);
  mcu_push(XH);
  mcu_push(CC);
 
  I0 = 1;
  I1 = 1;
  return 1;
}
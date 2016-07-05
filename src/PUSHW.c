#include "PUSHW.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

# define NEXT_OP *(++opcode)

/**  Please refer all the definations and marco in MCU_Operation.h
*

*/ 


uint8_t pushw_x(uint8_t *opcode){
  mcu_push(XL);
  mcu_push(XH);
  return 1;
}
uint8_t pushw_y(uint8_t *opcode){
  mcu_push(YL);
  mcu_push(YH);
  return 2; 
}

#include "CALLR.h"
#include "Description.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"


uint8_t callr_shortmem(uint8_t *opcode){
  *pcToLoad = PC + 2;

  mcu_push( *pcToLoad &0xFF );
  mcu_push((*pcToLoad &0xFF00)>>8 );
  *pcToLoad += GET_SHORT_MEM_SRC(opcode);
  return 2;  
}
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "InstructionTable.h"
#include "ADDW.h"
#include "ADD.h"
#include "ADC.h"
#include "NEG.h"
#include "NEGW.h"
#include "SUBW.h"
#include "SBC.h"
#include "CPL.h"
#include "CPLW.h"
#include "INC.h"
#include "INCW.h"
#include "DEC.h"
#include "DECW.h"
#include "NOP.h"
#include "CLR.h"
#include "CLRW.h"
#include "EXG.h"
#include "EXGW.h"
#include "MOV.h"
#include "RVF.h"
#include "CCF.h"
#include "RCF.h"
#include "SCF.h"
#include "SIM.h"
#include "RIM.h"
#include "TNZ.h"
#include "TNZW.h"
#include "BCP.h"
#include "TRAP.h"
#include "JP.h"
#include "JRA.h"
#include "JPF.h"
#include "JRXX.h"
#include "WFI.h"
#include "WFE.h"
#include "HALT.h"
#include "BREAK.h"
#include "IRET.h"
#include "BSET.h"
#include "BRES.h"
#include "BCPL.h"
#include "BCCM.h"
#include "BTJF.h"
#include "BTJT.h"
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "CException.h"
#include <malloc.h>
#include "Description.h"


// int main(void){
  
// }

void executeOneInstructon(uint8_t *opcode){
  CEXCEPTION_T err;
  int length;
 
  Try{
    length = executeInstructionAndReturnLength(opcode);
    
    if(*pcToLoad != 0xFFFFFF){
  
      SET_PC( *pcToLoad );
      *pcToLoad = 0xFFFFFF;
    }else{
      printf("in\n");
      SET_PC( PC+length );
    }
    
  }Catch(err){
    
    
  }
}
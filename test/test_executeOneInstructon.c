#include "unity.h"
#include "main.h"
#include "InstructionTable.h"
#include <stdio.h>
#include <stdint.h>
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

void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  pcToLoad = malloc(sizeof(uint32_t));
  *pcToLoad = 0xFFFFFF;
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
  free(pcToLoad);
}

void test_executeOneInstructon_given_instr_add_a_byte_should_increament_PC_by_2(void){

  SET_PC(0x03);
  
  uint8_t instr[] = {
    0xAB
  };
  
  executeOneInstructon(instr);
  TEST_ASSERT_EQUAL_INT32(0x5,PC);
  TEST_ASSERT_EQUAL_INT32(0xFFFFFF,*pcToLoad);
}

void test_executeOneInstructon_given_instr_jp_longmem_should_jump_to_longmem(void){

  SET_PC(0x03);
  uint8_t instr[] = {0XCC, 0x33, 0x77}; 
  
  executeOneInstructon(instr);
  TEST_ASSERT_EQUAL_INT32(0x3377,PC);
  TEST_ASSERT_EQUAL_INT32(0xFFFFFF,*pcToLoad);
}

void test_executeOneInstructon_given_instr_jpf_longptr_e_should_jump(void){

  SET_PC(0x03);
  uint8_t instr[] = {0X92, 0XAC, 0x77, 0x88}; 
  MEM_WRITE_BYTE( 0x7788, 0x01);
  MEM_WRITE_BYTE( 0x7789, 0x55);
  MEM_WRITE_BYTE( 0x778A, 0x77);
  
  executeOneInstructon(instr);
  TEST_ASSERT_EQUAL_INT32(0x015577,PC);
  TEST_ASSERT_EQUAL_INT32(0xFFFFFF,*pcToLoad);
}

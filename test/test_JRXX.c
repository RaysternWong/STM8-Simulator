#include "unity.h"
#include "JRXX.h"
#include "Description.h"
#include <stdint.h>
#include <stdio.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include "MCU_Operation.h"
#include <malloc.h>

void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
  SET_PC_WORD(0x1);   //PC was set  to 1
  pcToLoad = malloc(sizeof(uint32_t));
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
  free(pcToLoad);
}

void test_jrc(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrc(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrc(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25 , *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}


void test_jreq(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	Z = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jreq(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  Z = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jreq(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrf(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  *pcToLoad = 0;
	Z = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrf(instr));  
  TEST_ASSERT_EQUAL_INT16( 0 , *pcToLoad);    // never jump, *pcToLoad unchanged
}

void test_jrh(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	H = 0;
  TEST_ASSERT_EQUAL_INT8( 3, jrh(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  H = 1;
  TEST_ASSERT_EQUAL_INT8( 3, jrh(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrm(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	I0 = 0;
  TEST_ASSERT_EQUAL_INT8( 3, jrm(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  I0 = 1;
  I1 = 1;
  TEST_ASSERT_EQUAL_INT8( 3, jrm(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrmi(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	N = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrmi(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  N = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrmi(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrnc(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrnc(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrnc(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrne(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	Z = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrne(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  Z = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrne(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrnh(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	H = 1;
  TEST_ASSERT_EQUAL_INT8( 3, jrnh(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  H = 0;
  TEST_ASSERT_EQUAL_INT8( 3, jrnh(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrnm(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	I0 = 1;
	I1 = 1;
  TEST_ASSERT_EQUAL_INT8( 3, jrnm(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  I0 = 0;
  TEST_ASSERT_EQUAL_INT8( 3, jrnm(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrnv(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	V = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrnv(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  V = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrnv(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrpl(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	N = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrpl(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  N = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrpl(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrsge(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	N = 0;
	V = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrsge(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  N = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrsge(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrsgt(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
  Z = 1;

  TEST_ASSERT_EQUAL_INT8( 2, jrsgt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  N = 0;
  V = 0;
  Z = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrsgt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrsle(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
  Z = 0;
	N = 0;
	V = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrsle(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  Z = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrsle(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrslt(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	N = 0;
	V = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrslt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  N = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrslt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrt(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
  TEST_ASSERT_EQUAL_INT8( 2, jrt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25 , *pcToLoad); // always jump, *pcToLoad = 1 + 2 + 22 =  25;
}

void test_jruge(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jruge(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jruge(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrugt(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrugt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 0;
  Z = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrugt(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrule(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrule(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 1;
  Z = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrule(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrult(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	C = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrult(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  C = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrult(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}

void test_jrv(void){
  uint8_t instr[] = {0XAB, 0x22}; 
  
	V = 0;
  TEST_ASSERT_EQUAL_INT8( 2, jrv(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x3 , *pcToLoad);    // Condition false , *pcToLoad = PC + 2  =  3;
  
  V = 1;
  TEST_ASSERT_EQUAL_INT8( 2, jrv(instr));  
  TEST_ASSERT_EQUAL_INT16( 0x25, *pcToLoad); // Condition false , *pcToLoad = PC + 2 + 22 =  27;
}
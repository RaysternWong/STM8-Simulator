#include "unity.h"
#include "ReadS19.h"
#include "MCU_Operation.h"
#include "CPUConfig.h"
#include "Memory.h"
#include "ErrorObject.h"
#include <malloc.h>
#include "Description.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <CException.h>


void setUp(void){
  instantiateCPU();
  gpioInit(0x0, 0xFFFF);
}

void tearDown(void){
  free(cpu);
  free(gpioBlock);
}

void xtest_recordS1_gdfdg(void){
  char *line = "12345678";
  int i;
  char buffer[3] = {0,0,0};
  
  for(i=0; i < 20; i+=2){
    sscanf(&line[i], "%2s", buffer);
    printf("%s\n",buffer);
  }

  
  // uint8_t checkSum = 0x55 + 0x55 + 0x01 + 0x02;
  // printf("%x\n",checkSum);
  // printf("%x\n",~checkSum);
}

/** 
      record type  : S1
      byteCount    : 08 , which are 55,55,01,A9 (unit is two hex digits, indicating the number of bytes)
      address      : 0x5555
      data         : 0x01
      checkSum     : 0x54 ,which ~(0x55 + 0x55 + 0x01)
*/
void test_recordS1_given_string_is_S10855550154_and_record_01_to_address(void){

  char *line = "S10855550154";
  recordS1(line);
  
  TEST_ASSERT_EQUAL_INT8(0x01, MEM_READ_BYTE(0x5555));// test is 01 wrote into the address
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(0x5556)); // test the address empty
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(0x5554)); // test the address empty
}

 // uint8_t checkSum = (0x55 + 0x55 + 0xA1 + 0xB2 + 0xC3) & 0xFF;
  // printf("%x\n", checkSum);
  // printf("%x\n", ~checkSum);

/** 
      record type  : S1
      byteCount    : 0C ,which are 55,55,A1,B2,C3,3F
      address      : 0x5555
      data         : 0xA1, 0XB2 , 0XC3
      checkSum     : 0x3F ,which ~(0x55 + 0x55 + 0xA1 + 0xB2 + 0xC3)
*/
void test_recordS1_given_string_is_S1_0C_5555_A1_B2_C3_3F_and_record_A1_B2_C3_to_address(void){

  char *line = "S10C5555A1B2C33F";
 
  recordS1(line);
  
  TEST_ASSERT_EQUAL_INT8(0xA1, MEM_READ_BYTE(0x5555));
  TEST_ASSERT_EQUAL_INT8(0xB2, MEM_READ_BYTE(0x5556));
  TEST_ASSERT_EQUAL_INT8(0XC3, MEM_READ_BYTE(0x5557));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0x5558));
}


void xtest_readS19(void){
  readS19("C:\\Users\\D203C-01\\Desktop\\STM8-Simulator\\test\\support\\acia.s19");
}

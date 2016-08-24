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

/** 
      record type  : S1
      byteCount    : 03 , which are FF,FF,FE (unit is two hex digits, indicating the number of bytes)
      address      : 0xFFFF
      data         :  Not Exist
      checkSum     : 0xFE ,which ~(FF+FF)
*/
void test_getRecords_given_string_is_S903FFFFFE_should_get_the_3_records(void){
  char *line = "S903FFFFFE";
  uint8_t byteCount = 0, checkSum = 0;
  uint16_t address = 0;
 
  getRecords(&byteCount, &address, &checkSum, line);
  TEST_ASSERT_EQUAL_INT8(0x03, byteCount);
  TEST_ASSERT_EQUAL_INT8(0xFE, checkSum);
  TEST_ASSERT_EQUAL_INT16(0xFFFF, address);
}

/** 
      record type  : S1
      byteCount    : 04 , which are 55,55,01,54 (unit is two hex digits, indicating the number of bytes)
      address      : 0x5555
      data         : 0x01
      checkSum     : 0x54 ,which ~(0x55 + 0x55 + 0x01)
*/
void test_getRecords_given_string_is_S10855550154_should_get_the_3_records(void){
  char *line = "S10455550154";
  uint8_t byteCount = 0, checkSum = 0;
  uint16_t address = 0;
  
  getRecords(&byteCount, &address, &checkSum, line);
  TEST_ASSERT_EQUAL_INT8(0x04, byteCount);
  TEST_ASSERT_EQUAL_INT8(0x54, checkSum);
  TEST_ASSERT_EQUAL_INT16(0x5555, address);
}


/** 
      record type  : S1
      byteCount    : 06 ,which are 33,33,A1,B2,C3,3F
      address      : 0x3333
      data         : 0xA1, 0XB2 , 0XC3
      checkSum     : 0x3F ,which ~(0x33 + 0x33 + 0xA1 + 0xB2 + 0xC3)
*/
void test_getRecords_given_string_is_S10C3333A1B2C33F_should_get_the_3_records(void){
  char *line = "S1063333A1B2C33F";
  uint8_t byteCount = 0, checkSum = 0;
  uint16_t address = 0;
 
  getRecords(&byteCount, &address, &checkSum, line);
  TEST_ASSERT_EQUAL_INT8(0x06, byteCount);
  TEST_ASSERT_EQUAL_INT8(0x3F, checkSum);
  TEST_ASSERT_EQUAL_INT16(0x3333, address);
}




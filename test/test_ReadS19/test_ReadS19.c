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



/** Example inside acia.s19  (test/support)
      record type  : S9
      byteCount    : 03 , which are FF,FF,FE (unit is two hex digits, indicating the number of bytes)
      address      : 0xFFFF
      data         :  Not Exist
      checkSum     : 0xFE ,which ~(03+FF+FF)
*/
void test_S19Interpret_given_string_is_S903FFFFFE__shouldnot_record_because_data_is_not_exist(void){
  char *line = "S903FFFFFE";
  S19Interpret(line);
  
  uint16_t address = 0x2345;
  TEST_ASSERT_EQUAL_INT8(0x00, MEM_READ_BYTE(0xFFFF)); // test is FFFF has no write in data
}

void test_S19Interpret_given_string_has_wrong_checkSum_should_throw_exception(void){
  CEXCEPTION_T err;
  char *line = "S903FFFF88";  //FE change to 88
  
  Try{
  S19Interpret(line);
  TEST_FAIL_MESSAGE("Expected ERR_CHECKSUM_WRONG");
  
  }Catch(err){
    TEST_ASSERT_EQUAL_MESSAGE(ERR_CHECKSUM_WRONG, err, "Expected ERR_CHECKSUM_WRONG");
  }
}

/** 
      record type  : S1
      byteCount    : 04 , which are 55,55,01,50 (unit is two hex digits, indicating the number of bytes)
      address      : 0x5555
      data         : 0x01
      checkSum     : 0x50 ,which ~(0x04 + 0x55 + 0x55 + 0x01)
*/
void test_S19Interpret_given_string_is_S10455550150_and_record_01_to_address(void){

  char *line = "S10455550150";
  S19Interpret(line);
  
  TEST_ASSERT_EQUAL_INT8(0x01, MEM_READ_BYTE(0x5555));// test is 0x01 wrote into the address
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(0x5556)); // test is the address empty
  TEST_ASSERT_EQUAL_INT8(0x0, MEM_READ_BYTE(0x5554)); // test is the address empty
}

 // uint8_t checkSum = (0x55 + 0x55 + 0xA1 + 0xB2 + 0xC3) & 0xFF;
  // printf("%x\n", checkSum);
  // printf("%x\n", ~checkSum);

/** 
      record type  : S1
      byteCount    : 06 ,which are 55,55,A1,B2,C3,3F
      address      : 0x5555
      data         : 0xA1, 0XB2 , 0XC3
      checkSum     : 0x39 ,which ~(0x06 + 0x55 + 0x55 + 0xA1 + 0xB2 + 0xC3)
*/
void test_S19Interpret_given_string_is_S1_06_5555_A1_B2_C3_39_and_record_A1_B2_C3_to_address(void){

  char *line = "S1065555A1B2C339";
 
  S19Interpret(line);
  
  TEST_ASSERT_EQUAL_INT8(0xA1, MEM_READ_BYTE(0x5555));
  TEST_ASSERT_EQUAL_INT8(0xB2, MEM_READ_BYTE(0x5556));
  TEST_ASSERT_EQUAL_INT8(0XC3, MEM_READ_BYTE(0x5557));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0x5558));
}

/** Example inside acia.s19  (test/support)
      record type  : S1
      byteCount    : 14, from 80 -> 22
      address      : 0x80E0
      data         : 0x4A to 0xF6
      checkSum     : 0x3F , sum from 14 to 22 
*/
void test_S19Interpret_given_string_is_S11480E04A34352C4A359A8D0080948D0080AD20F622(void){

  char *line = "S11480E04A34352C4A359A8D0080948D0080AD20F622";
 
  S19Interpret(line);
  
  TEST_ASSERT_EQUAL_INT8(0x4A, MEM_READ_BYTE(0x80E0));
  TEST_ASSERT_EQUAL_INT8(0x34, MEM_READ_BYTE(0x80E1));
  TEST_ASSERT_EQUAL_INT8(0x35, MEM_READ_BYTE(0x80E2));
  TEST_ASSERT_EQUAL_INT8(0x2C, MEM_READ_BYTE(0x80E3));
  TEST_ASSERT_EQUAL_INT8(0x4A, MEM_READ_BYTE(0x80E4));
  TEST_ASSERT_EQUAL_INT8(0x35, MEM_READ_BYTE(0x80E5));
  TEST_ASSERT_EQUAL_INT8(0x9A, MEM_READ_BYTE(0x80E6));
  TEST_ASSERT_EQUAL_INT8(0x8D, MEM_READ_BYTE(0x80E7));
  TEST_ASSERT_EQUAL_INT8(0x00, MEM_READ_BYTE(0x80E8));
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(0x80E9));
  TEST_ASSERT_EQUAL_INT8(0x94, MEM_READ_BYTE(0x80EA));
  TEST_ASSERT_EQUAL_INT8(0x8D, MEM_READ_BYTE(0x80EB));
  TEST_ASSERT_EQUAL_INT8(0x00, MEM_READ_BYTE(0x80EC));
  TEST_ASSERT_EQUAL_INT8(0x80, MEM_READ_BYTE(0x80ED));
  TEST_ASSERT_EQUAL_INT8(0xAD, MEM_READ_BYTE(0x80EE));
  TEST_ASSERT_EQUAL_INT8(0x20, MEM_READ_BYTE(0x80EF));
  TEST_ASSERT_EQUAL_INT8(0xF6, MEM_READ_BYTE(0x80F0));
  TEST_ASSERT_EQUAL_INT8(0, MEM_READ_BYTE(0x80F1));
}

// Please pass in a valid path of S19 file
void test_readS19(void){
  readS19("C:\\Users\\Raydivine\\Desktop\\STM8-Simulator\\test\\support\\acia.s19");
 // readS19("C:\\Users\\D203C-01\\Desktop\\STM8-Simulator\\test\\support\\acia.s19");
}
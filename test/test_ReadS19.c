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



void setUp(void)
{
}

void tearDown(void)
{
}

void test_initInStreamshould_malloc_correctly(void){
  InStream *in = initInStream();
  TEST_ASSERT_NOT_NULL(in);
	TEST_ASSERT_EQUAL(0, in->byteToRead);
	TEST_ASSERT_EQUAL(8, in->bitIndex);
  freeInStream(&in);
}

void test_readS19(void){
  readS19("C:\\Users\\D203C-01\\Desktop\\STM8-Simulator\\test\\support\\acia.s19");


}

void xtest_openInStream_given_open_a_not_exist_file(void){
  InStream *in = initInStream();
    
  in = openInStream("acrewrweia.s19", "r" , in);
  
  //TEST_ASSERT_EQUAL_STRING("acia.s19", in->fileName);
}
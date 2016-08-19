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

void test_readS19(void){
  readS19("C:\\Users\\D203C-01\\Desktop\\STM8-Simulator\\test\\support\\acia.s19");
}

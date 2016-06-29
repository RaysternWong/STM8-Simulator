#include "unity.h"
#include "Memory.h"
#include "CPUConfig.h"


#define RAM_START_ADDR          0x0
#define RAM_END_ADDR            0x3FF

#define RES1_START_ADDR         0X800
#define EEPROM_START_ADDR       0X4000
#define RES2_START_ADDR         0X4280
#define OPTION_BYTE_START_ADDR  0X4800
#define RES3_START_ADDR         0X480B
#define UNIQUE_ID_START_ADDR    0X4865
#define RES4_START_ADDR         0X4871
#define GPIO_START_ADDR         0X5000
#define RES5_START_ADDR         0X5800
#define CPU_START_ADDR          0x7F00
#define IRQ_START_ADDR          0X8000
#define FLASH_START_ADDR        0X8080
#define RES6_START_ADDR         0XA000

void setUp(void)
{
}

void tearDown(void)
{
}

void test_writeValueToTheAddress_given_write_to_address_0x0000(void)
{
  uint16_t  addr  = 0x0000;
  uint8_t   value = 0xA;
  
  writeValueToTheAddress( addr, value);
  
  uint8_t result = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xA, result);
}

void test_writeValueToTheAddress_given_write_to_address_0x288(void)
{
  uint16_t  addr  = 0x288;
  uint8_t   value = 0xA;
  
  writeValueToTheAddress( addr, value);
  
  uint8_t result = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xA, result);
}


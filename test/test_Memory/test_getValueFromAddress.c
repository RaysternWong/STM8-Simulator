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

void test_getValueFromAddress_given_address_is_0x288(void)
{
  uint16_t addr = 0x288;
  
  ram_addr[0x288] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x3FF(void)
{
  uint16_t addr = 0x3FF;
  
  ram_addr[0x3FF] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x0(void)
{
  uint16_t addr = 0x0;
  
  ram_addr[0x0] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x800(void)
{
  uint16_t addr = 0x800;
  
  reserved1_addr[0x800 -RES1_START_ADDR] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x3FFF(void)
{
  uint16_t addr = 0x3FFF;
  
  reserved1_addr[0x3FFF -RES1_START_ADDR] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x4000(void)
{
  uint16_t addr = 0x4000;
  
  eeprom_addr[0x4000 -EEPROM_START_ADDR] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}

void test_getValueFromAddress_given_address_is_0x57FF(void)
{
  uint16_t addr = 0x57FF;
  
  gpio_addr[0x57FF - GPIO_START_ADDR] = 0xC;
  
  uint8_t value = getValueFromAddress(addr);
  
	TEST_ASSERT_EQUAL_INT8(0xC, value);
}


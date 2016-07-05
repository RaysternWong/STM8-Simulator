#include "Description.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"
#include "MCU_Operation.h"

uint16_t getlongmem(uint8_t *opcode){
  uint8_t      msb = *(++opcode);
  uint8_t      lsb = *(++opcode);
  uint16_t longmem = getBigEndianWord( msb , lsb );
  return longmem;

}

uint8_t getValueHoldByLongmem(uint8_t *opcode){
  uint16_t longmem = getlongmem(opcode);
  uint8_t    value = MEM_READ_BYTE(longmem);
  return value;
}
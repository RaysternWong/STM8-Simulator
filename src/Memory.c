#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "CPUConfig.h"

MemoryBlock *ramBlock;
MemoryBlock *cpuBlock;
MemoryBlock *flashBlock;

MemoryMap memoryTable[0x280] = {

  // [0X00] = ramMemory,
  // [0X01] = ramMemory,
  // [0X02] = ramMemory,
  // [0X03] = ramMemory,
  // [0X04] = ramMemory,
  
  // [0X7F] = cpuMemory,

};

MemoryBlock *createMemoryBlock( uint32_t startAddr, uint32_t size){
  MemoryBlock *mb = malloc(400 + sizeof(MemoryBlock));
  mb->startAddr =& startAddr;
  mb->size = size;
  mb->data = malloc(size * sizeof(uint8_t));
  return mb;
}

uint8_t ramMemory(Mode mode, uint32_t address, uint8_t data)
{

  if(mode == MEM_WRITE){
    ramBlock->data[address] = data;
  }
  
  if(mode == MEM_READ){
    return ( RAM_ARR(address) );
  }
}

uint8_t cpuMemory(Mode mode, uint32_t address, uint8_t data)
{
  if(mode == MEM_WRITE){
    cpuBlock->data[address-CPU_START_ADDR] = data;
  }
  
  if(mode == MEM_READ){
    return ( cpuBlock->data[address-CPU_START_ADDR] );
  }
}

uint8_t eepromMemory(Mode mode, uint32_t address, uint8_t data)
{
  if(mode == MEM_READ){
    return ( flashBlock->data[address-EEPROM_START_ADDR] );
  }
}

void setMemoryTable(uint8_t (*memoryFunc)(Mode mode, uint32_t address, uint8_t data), uint32_t start, uint32_t end)
{
  int i;
  start /= 0x100;
  end /= 0x100;
  
  for( i=start ; i<= end ; i++)
    memoryTable[i] = memoryFunc;
}




#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "CPUConfig.h"
#include "MCU_Operation.h"
#include "Description.h"
#include "ErrorObject.h"

CPU_t *cpu;

MemoryBlock *ramBlock, *cpuBlock, *flashBlock;

void instantiateCPU(void)
{
  cpu = malloc( sizeof(CPU_t) );
}

MemoryMap memoryTable[0x280] = {

  // [0X00] = ramMemory,
  // [0X01] = ramMemory,
  // [0X02] = ramMemory,
  // [0X03] = ramMemory,
  // [0X04] = ramMemory,
  
  // [0X7F] = cpuMemory,

};

MemoryBlock *createMemoryBlock( uint32_t startAddr, uint32_t size){
  MemoryBlock *mb = malloc(sizeof(MemoryBlock));
  mb->startAddr =& startAddr;
  mb->size = size;
  mb->data = malloc(size);
  return mb;
}

void ramInit(void){
   ramBlock = createMemoryBlock(RAM_START_ADDR, RAM_SIZE);
   setMemoryTable( ramMemory , RAM_START_ADDR , RAM_SIZE );
}


uint32_t noMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data){
  if(mode == MEM_READ)
    ThrowError(ERR_UNINITIALIZED_ADDRESS, "Access uninitialized memory from Type: MEM_READ Address: %x\t", address);
  if(mode == MEM_WRITE)
    ThrowError(ERR_UNINITIALIZED_ADDRESS, "Access uninitialized memory from Type: MEM_READ Address: %x\t Size %d\n", address, size);
}

uint32_t ramMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data)
{
  if(mode == MEM_READ){
    if(size == 1)  
      return ( RAM_ARR(address) );
    if(size == 2)  
      return ( getBigEndianWordFromAddress(address) );
    return ( getBigEndianExtFromAddress(address) );
  }
  
  
  if(mode == MEM_WRITE){
    ramBlock->data[address] = data;
  }
  

}

uint32_t cpuMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data)
{
  if(mode == MEM_WRITE){
    cpuBlock->data[address-CPU_START_ADDR] = data;
  }
  
  if(mode == MEM_READ){
    return ( cpuBlock->data[address-CPU_START_ADDR] );
  }
}

uint32_t eepromMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data)
{
  if(mode == MEM_READ){
    return ( flashBlock->data[address-EEPROM_START_ADDR] );
  }
}

void setMemoryTable(uint32_t (*memoryFunc)(Mode mode, uint32_t address, uint8_t size, uint8_t data), uint32_t start, uint32_t end)
{
  int i;
  start /= 0x100;
  end /= 0x100;
  
  for( i=start ; i<= end ; i++)
    memoryTable[i] = memoryFunc;
}

void clearConditionCodeRegister(Flag *ccR)
{
  ccR->full = 0;
  (ccR->bits).v  = 0;
  (ccR->bits).l1 = 0;
  (ccR->bits).h  = 0;
  (ccR->bits).l0 = 0;
  (ccR->bits).n  = 0;
  (ccR->bits).z  = 0;
  (ccR->bits).c  = 0;
}


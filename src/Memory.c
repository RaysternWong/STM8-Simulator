#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "CPUConfig.h"
#include "MCU_Operation.h"
#include "Description.h"
#include "ErrorObject.h"

CPU_t *cpu;

MemoryBlock *ramBlock, *gpioBlock, *eepromBlock, *flashBlock, *cpuBlock;

MemoryMap memoryTable[0x280] = {};

MemoryBlock *createMemoryBlock( uint32_t startAddr, uint32_t size){
  MemoryBlock *mb = malloc(sizeof(MemoryBlock));
  mb->startAddr =& startAddr;
  mb->size = size;
  mb->data = malloc(size);
  return mb;
}

void memoryInit(void){
                              // 0x00          0x027FFF
  setMemoryTable(noMemory, STM8_START_ADDR, STM8_END_ADDR );
  ramInit   (RAM_START_ADDR   , RAM_SIZE   ); //0x0 ---> 0x03FF
  gpioInit  (GPIO_START_ADDR  , GPIO_SIZE  ); //0x5000----> 0x57FF
  eepromInit(EEPROM_START_ADDR, EEPROM_SIZE); //0x4000----> 0x427F
  flashInit (OPTION_BYTE_START_ADDR, GPIO_START_ADDR - 1- OPTION_BYTE_START_ADDR); //0x4800 --> 0x4FFF
}

void memoryBlockInit( MemoryBlock **block, 
                      uint32_t    (*memoryFunc)(Mode mode, uint32_t address, uint8_t size, uint8_t data), 
                      uint32_t    startAddr,
                      uint32_t    size
                    ){
  *block = malloc(sizeof(MemoryBlock));
  (*block)->startAddr =& startAddr;
  (*block)->size = size;
  (*block)->data = malloc(size);  
  setMemoryTable( memoryFunc , startAddr , size );
}



void memoryFree(void){
  free(ramBlock);
  free(gpioBlock);
  free(eepromBlock);
  free(flashBlock);
}

void instantiateCPU(void){
  cpu = malloc( sizeof(CPU_t) );
  //cpu->a = 0x7F00;
}

void ramInit(uint32_t address, uint32_t size){
   ramBlock = createMemoryBlock(address, size);
   setMemoryTable( ramMemory , address , size );
}

void gpioInit(uint32_t address, uint32_t size){
   gpioBlock = createMemoryBlock(address, size);
   setMemoryTable( gpioMemory , address , size );
}

void eepromInit(uint32_t address, uint32_t size){
   eepromBlock = createMemoryBlock(address, size);
   setMemoryTable( eepromMemory , address , size );
}

void flashInit(uint32_t address, uint32_t size){
   flashBlock = createMemoryBlock(address, size);
   setMemoryTable( flashMemory , address , size );
}

void cpuInit(uint32_t address, uint32_t size){
  cpuBlock = createMemoryBlock(address, size);
  setMemoryTable( cpuMemory , address , size );
  
  cpu = (CPU_t) cpuBlock;
}

uint32_t noMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data){
  
  if(mode == MEM_READ)
    ThrowError(ERR_UNINITIALIZED_ADDRESS, "Attempt to read %d byte start from address 0x%x\n"   , size, address);
  ThrowError(ERR_UNINITIALIZED_ADDRESS, "Attempt to write data 0x%x start from address 0x%x\n", data, address);
}

uint32_t ramMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data)
{
  if(mode == MEM_READ){
    return ( size == 1 ? RAM_ARR(address) : 
             size == 2 ? getBigEndianWordFromAddress(address) : getBigEndianExtFromAddress(address) );             
    // if(size == 1)  
      // return ( RAM_ARR(address) );
    // if(size == 2)  
      // return ( getBigEndianWordFromAddress(address) );
    // return ( getBigEndianExtFromAddress(address) );
  }
 
  if(mode == MEM_WRITE){
    RAM_ARR(address) = data;
  }
}

uint32_t gpioMemory(Mode mode, uint32_t address, uint8_t size, uint8_t data){
  if(mode == MEM_READ){
    if(size == 1)  
      return ( GPIO_ARR(address) );
    if(size == 2)  
      return ( getBigEndianWordFromAddress(address) );
    return ( getBigEndianExtFromAddress(address) );
  }
  
  if(mode == MEM_WRITE)
    GPIO_ARR(address) = data;  
}

uint32_t eepromMemory  (Mode mode, uint32_t address, uint8_t size, uint8_t data){
  
}

uint32_t flashMemory   (Mode mode, uint32_t address, uint8_t size, uint8_t data){
  
}

uint32_t cpuMemory     (Mode mode, uint32_t address, uint8_t size, uint8_t data){
  
}

void setMemoryTable(uint32_t (*memoryFunc)(Mode mode, uint32_t address, uint8_t size, uint8_t data), uint32_t start, uint32_t end){
  int i;
  start /= 0x100;
  end /= 0x100;
  
  for( i=start ; i<= end ; i++)
    memoryTable[i] = memoryFunc;
}

void clearConditionCodeRegister(Flag *ccR){
  ccR->full = 0;
  (ccR->bits).v  = 0;
  (ccR->bits).l1 = 0;
  (ccR->bits).h  = 0;
  (ccR->bits).l0 = 0;
  (ccR->bits).n  = 0;
  (ccR->bits).z  = 0;
  (ccR->bits).c  = 0;
}


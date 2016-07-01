#include "Memory.h"
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "CPUConfig.h"

#define RAM_ARR(addr) ( ramBlock->data[addr-RAM_START_ADDR]  )

MemoryBlock *ramBlock;
MemoryBlock *cpuBlock;
MemoryBlock *flashBlock;

MemoryMap memoryTable[0x280] = {

  [0X00] = ramMemory,
  [0X01] = ramMemory,
  [0X02] = ramMemory,
  [0X03] = ramMemory,
  [0X04] = ramMemory,

};


MemoryBlock *createMemoryBlock( uint32_t startAddr, uint16_t size){
  MemoryBlock *mb = malloc(400 + sizeof(MemoryBlock));
  *(mb->startAddr) = startAddr;
  mb->size = size;
  
  return mb;
}

uint8_t ramMemory(Mode mode, uint32_t address, uint8_t data)
{
  if(mode == MEM_WRITE){
    RAM_ARR(address) = data;
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



















Memory ram_addr         [RAM_SIZE];
Memory reserved1_addr   [RES1_SIZE];
Memory eeprom_addr      [EEPROM_SIZE];
Memory reserved2_addr   [RES2_SIZE];
Memory optionByte_addr  [OPTION_BYTE_SIZE];
Memory reserved3_addr   [RES3_SIZE];
Memory uniqueID_addr    [UNIQUE_ID_SIZE];
Memory reserved4_addr   [RES4_SIZE];
Memory gpio_addr        [GPIO_SIZE];
Memory reserved5_addr   [RES5_SIZE];
Memory cpu_addr         [CPU_SIZE];
Memory interrupt_addr   [IRQ_SIZE];
Memory flash_addr       [FLASH_SIZE];
Memory reserved6_addr   [RES6_SIZE];

void readCPU(void)
{
  cpu->a = cpu_addr[0x00];
}


void writeCPU(void)
{
  cpu_addr[0x00] = cpu->a;
  cpu_addr[0x01] = cpu->pce;
  cpu_addr[0x02] = cpu->pch;
  cpu_addr[0x03] = cpu->pcl;
  cpu_addr[0x04] = cpu->xh;
  cpu_addr[0x05] = cpu->xl;
  cpu_addr[0x06] = cpu->yh;
  cpu_addr[0x07] = cpu->yl;
  cpu_addr[0x08] = cpu->sph;
  cpu_addr[0x09] = cpu->spl;
  cpu_addr[0x0A] = (cpu->ccr).full;
}


/** Notice :
*   To save the code size, the if else statements below are arrange based on the "define valuue" from small to big
*   so the checking statement is simplied
*
*/
uint8_t getValueFromAddress(uint32_t addr)
{
  if( addr  <= RAM_END_ADDR){
    return ram_addr[addr];
  }
  
  else if( addr < EEPROM_START_ADDR ){
    return reserved1_addr[addr - RES1_START_ADDR ];
  }
  
  else if( addr < RES2_START_ADDR ){
    return eeprom_addr[addr - EEPROM_START_ADDR ];
  }
  
  else if( addr < OPTION_BYTE_START_ADDR ){
    return reserved2_addr[addr - RES2_START_ADDR ];
  }
  
  else if( addr < RES3_START_ADDR ){
    return optionByte_addr[addr - OPTION_BYTE_START_ADDR];
  }
  
  else if( addr < UNIQUE_ID_START_ADDR ){
    return reserved3_addr[addr - RES3_START_ADDR ];
  }
  
  else if( addr < RES4_START_ADDR ){
    return uniqueID_addr[addr - UNIQUE_ID_START_ADDR ];
  }
  
  else if( addr < GPIO_START_ADDR ){
    return reserved4_addr[addr - RES4_START_ADDR ];
  }
  
  else if( addr < RES5_START_ADDR ){
    return gpio_addr[addr - GPIO_START_ADDR ];
  }
  
  else if( addr < CPU_START_ADDR ){
    return reserved5_addr[addr - RES5_START_ADDR ];
  }
  
  else if( addr < IRQ_START_ADDR ){
    return cpu_addr[addr - CPU_START_ADDR ];
  }
  else if( addr < FLASH_START_ADDR ){
    return interrupt_addr[addr - IRQ_START_ADDR ];
  }
  
  else if( addr < RES6_START_ADDR ){
    return flash_addr[addr - FLASH_START_ADDR ];
  }
  
  else{
    return reserved6_addr[addr - RES6_START_ADDR ];
  }
}

void  writeValueToTheAddress(uint32_t addr, uint8_t value)
{
  if( addr  <= RAM_END_ADDR){
     ram_addr[addr] = value;
  }
  
  else if( addr < EEPROM_START_ADDR ){
     reserved1_addr[addr - RES1_START_ADDR ] = value;
  }
  
  else if( addr < RES2_START_ADDR ){
     eeprom_addr[addr - EEPROM_START_ADDR ] = value;
  }
  
  else if( addr < OPTION_BYTE_START_ADDR ){
     reserved2_addr[addr - RES2_START_ADDR ] = value;
  }
  
  else if( addr < RES3_START_ADDR ){
     optionByte_addr[addr - OPTION_BYTE_START_ADDR] = value;
  }
  
  else if( addr < UNIQUE_ID_START_ADDR ){
     reserved3_addr[addr - RES3_START_ADDR ] = value;
  }
  
  else if( addr < RES4_START_ADDR ){
     uniqueID_addr[addr - UNIQUE_ID_START_ADDR ] = value;
  }
  
  else if( addr < GPIO_START_ADDR ){
     reserved4_addr[addr - RES4_START_ADDR ] = value;
  }
  
  else if( addr < RES5_START_ADDR ){
     gpio_addr[addr - GPIO_START_ADDR ] = value;
  }
  
  else if( addr < CPU_START_ADDR ){
     reserved5_addr[addr - RES5_START_ADDR ] = value;
  }
  
  else if( addr < IRQ_START_ADDR ){
     cpu_addr[addr - CPU_START_ADDR ] = value;
  }
  else if( addr < FLASH_START_ADDR ){
     interrupt_addr[addr - IRQ_START_ADDR ] = value;
  }
  
  else if( addr < RES6_START_ADDR ){
     flash_addr[addr - FLASH_START_ADDR ] = value;
  }
  
  else{
     reserved6_addr[addr - RES6_START_ADDR ] = value;
  }
}
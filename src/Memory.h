#ifndef Memory_H
#define Memory_H
#include "CPUConfig.h"
#include <stdint.h>

#define RAM_SIZE          0x3FF
#define RES1_SIZE         0X37FF
#define EEPROM_SIZE       0X27F
#define RES2_SIZE         0X57F
#define OPTION_BYTE_SIZE  0XA
#define RES3_SIZE         0X59
#define UNIQUE_ID_SIZE    0XB
#define RES4_SIZE         0X8E
#define GPIO_SIZE         0X7FF
#define RES5_SIZE         0X26FF
#define CPU_SIZE          0xFF
#define IRQ_SIZE          0X7F
#define FLASH_SIZE        0X1F7F
#define RES6_SIZE         0X1DFF

#define STM8_START_ADDR         0X0
#define STM8_END_ADDR         0x027FFF

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

#define RAM_ARR(addr)     ( ramBlock->data[addr-RAM_START_ADDR]  )
#define GPIO_ARR(addr)    ( gpioBlock->data[addr-RAM_START_ADDR]  )
#define CPU_ARR(addr)     ( cpuBlock->data[addr-RAM_START_ADDR]  )
#define EEPROM_ARR(addr)  ( eepromBlock->data[addr-RAM_START_ADDR]  )
#define FLASH_ARR(addr)   ( flashBlock->data[addr-RAM_START_ADDR]  )

typedef enum{
  MEM_READ,
  MEM_WRITE,
}Mode;

typedef struct{
  uint32_t  *startAddr;
  uint16_t  size;
  uint8_t   *data; // array pointer, containing data
}MemoryBlock;

typedef uint32_t (*MemoryMap)(Mode mode, uint32_t address, uint8_t size, uint32_t data);

MemoryBlock *createMemoryBlock( uint32_t startAddr, uint32_t size);
MemoryMap   memoryTable[0x280] ;

extern MemoryBlock *ramBlock, *gpioBlock, *eepromBlock, *flashBlock, *cpuBlock;

void assignNoMemoryToWholeMemoryTable();
void setMemoryTable(uint32_t (*memoryFunc)(Mode mode, uint32_t address, uint8_t size, uint32_t data), uint32_t startAddr, uint32_t memSize);

void clearConditionCodeRegister(Flag *ccR);
void memoryInit(void);
void memoryFree(void);
void ramInit        (uint32_t address, uint32_t size);
void gpioInit       (uint32_t address, uint32_t size);
void eepromInit     (uint32_t address, uint32_t size);
void flashInit      (uint32_t address, uint32_t size);
void cpuInit        (uint32_t address, uint32_t size);

uint32_t noMemory      (Mode mode, uint32_t address, uint8_t size, uint32_t data);
uint32_t ramMemory     (Mode mode, uint32_t address, uint8_t size, uint32_t data);
uint32_t gpioMemory    (Mode mode, uint32_t address, uint8_t size, uint32_t data);
uint32_t eepromMemory  (Mode mode, uint32_t address, uint8_t size, uint32_t data);
uint32_t flashMemory   (Mode mode, uint32_t address, uint8_t size, uint32_t data);
uint32_t cpuMemory     (Mode mode, uint32_t address, uint8_t size, uint32_t data);



CPU_t *createCPU(void);




void memoryBlockInit( MemoryBlock **block, 
                      uint32_t    (*memoryFunc)(Mode mode, uint32_t address, uint8_t size, uint8_t data), 
                      uint32_t    startAddr,
                      uint32_t    size
                    );
#endif // Memory_H


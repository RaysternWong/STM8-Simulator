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

typedef enum{
  MEM_READ,
  MEM_WRITE,
}Mode;

typedef struct{
  uint32_t *startAddr;
  uint16_t  size;
  uint8_t   data[0];
}MemoryBlock;

typedef uint8_t (*MemoryMap)(Mode mode, uint32_t address, uint8_t size);

MemoryMap memoryTable[0x280] ;

extern MemoryBlock *ramBlock;
extern MemoryBlock *cpuBlock;
extern MemoryBlock *flashBlock;


MemoryBlock *createMemoryBlock( uint32_t startAddr, uint16_t size);
uint8_t ramMemory(Mode mode, uint32_t address, uint8_t data);
uint8_t cpuMemory(Mode mode, uint32_t address, uint8_t data);
uint8_t eepromMemory(Mode mode, uint32_t address, uint8_t data);




typedef uint8_t Memory;

extern Memory ram_addr         [RAM_SIZE];
extern Memory reserved1_addr   [RES1_SIZE];
extern Memory eeprom_addr      [EEPROM_SIZE];
extern Memory reserved2_addr   [RES2_SIZE];
extern Memory optionByte_addr  [OPTION_BYTE_SIZE];
extern Memory reserved3_addr   [RES3_SIZE];
extern Memory uniqueID_addr    [UNIQUE_ID_SIZE];
extern Memory reserved4_addr   [RES4_SIZE];
extern Memory gpio_addr        [GPIO_SIZE];
extern Memory reserved5_addr   [RES5_SIZE];
extern Memory cpu_addr         [CPU_SIZE];
extern Memory interrupt_addr   [IRQ_SIZE];
extern Memory flash_addr       [FLASH_SIZE];
extern Memory reserved6_addr   [RES6_SIZE];

void    writeCPU(void);
void    readCPU(void);

uint8_t getValueFromAddress   (uint32_t addr);
void    writeValueToTheAddress(uint32_t addr, uint8_t value);

#endif // Memory_H

